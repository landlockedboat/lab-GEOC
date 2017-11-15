#include <geoc/io/screen/ScreenInput.h>
#include <geoc/io/screen/ScreenState.h>
#include <geoc/io/screen/IdleState.h>
#include <geoc/io/input/Input.h>
#include <geoc/scene/SceneManager.h>
#include <geoc/camera/Camera.h>
#include <geoc/math/Math.h>
#include <geoc/math/Vector.h>
#include <geoc/gfx/Graphics.h>
#include <map>

#include <cstdio>
#include <iostream>


using namespace geoc;
using namespace std;


typedef std::map<Keyboard::key, IScreenState*> StateTransitions;
typedef pair<Keyboard::key, IScreenState*> StateTransition;


struct geoc::ScreenInput_Impl
{
    IScreenState*       currentState;
    IScreenState*       idleState;
    const Camera&       cam;
    const SceneManager& sceneMgr;
    StateTransitions    transitions;
    
    ScreenInput_Impl(const Camera& camera, const SceneManager& scenemgr)
        : cam(camera), sceneMgr(scenemgr) {}
};


ScreenInput::ScreenInput(const Camera& cam, const SceneManager& sceneMgr)
    : impl(new ScreenInput_Impl(cam, sceneMgr))
{
    impl->idleState		= new IdleState;
    impl->currentState	= impl->idleState;
    setTransition(Keyboard::Key_space, impl->idleState);
}


ScreenInput::~ScreenInput()
{
    if (impl)
    {
        foreach (StateTransition transition, impl->transitions)
        {
            if (transition.second) safe_delete(transition.second);
        }
        impl->transitions.clear();
    }
}


char ScreenInput::mouseRightClicked(const ScreenPos& pos)
{
    Vector3 world_pos = Math::viewportToObject(pos, impl->cam, impl->sceneMgr);
    return impl->currentState->mouseRightClick(world_pos);
}


char ScreenInput::mouseClicked(const ScreenPos& pos)
{
    Vector3 world_pos = Math::viewportToObject(pos, impl->cam, impl->sceneMgr);
    return impl->currentState->mouseClick(world_pos);
}


char ScreenInput::mouseMoved(const ScreenPos& pos)
{
    Vector3 world_pos = Math::viewportToObject(pos, impl->cam, impl->sceneMgr);
    return impl->currentState->mouseMove(world_pos);
}


char ScreenInput::keyPressed(Keyboard::key key, const ScreenPos& pos)
{
    char request = 0;
    
    // Search for transitions.
    foreach (StateTransition transition, impl->transitions)
    {
        if (transition.first == key)
        {
            impl->currentState->cancel();
            impl->currentState = transition.second;
            Vector3 world_pos = Math::viewportToObject(pos, impl->cam, impl->sceneMgr);
            request |= impl->currentState->mouseMove(world_pos);
            request |= GEOC_APP_REDISPLAY | GEOC_APP_STATUS_BAR_UPDATE;
            break;
        }
    }
    
    request |= impl->currentState->keyPressed(key);
    return request;
}


void ScreenInput::draw(Graphics& gfx)
{
    impl->currentState->draw(gfx);
}


void ScreenInput::setTransition(Keyboard::key key, IScreenState* state)
{
    impl->transitions[key] = state;
}


void ScreenInput::setState(IScreenState* state)
{
    impl->currentState = state;
}


const char* ScreenInput::stateDescription() const
{
    return impl->currentState->description();
}
