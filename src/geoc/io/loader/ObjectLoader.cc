#include <geoc/io/loader/ObjectLoader.h>
#include <geoc/GeocException.h>
#include <geoc/io/File_utils.h>
#include <sstream>

#include <cstdio>
#include <iostream>


using namespace geoc;
using namespace std;


ObjectLoader::~ObjectLoader()
{
    LoaderList_iterator loader;
    foreach (ILoader* loader, loaders)
    {
        delete loader;
    }
    loaders.clear();
}


void ObjectLoader::attach(ILoader* loader)
{
    loaders.push_back(loader);
}


void ObjectLoader::detach(ILoader* loader)
{
    loaders.remove(loader);
    delete loader;
}


void ObjectLoader::load(const char* filename)
{
    fstream f;
    openFile(f, filename, std::fstream::in | std::fstream::binary);
    
    GEOC_LOADER_CODE result;
    bool done = false;
    
    while (!f.eof() && !done)
    {
        bool dataParsed = false;
        streampos next_section = f.tellg();
        
        // Save the input cursor.
        streampos current_section = f.tellg();
        
        // Let each loader get a chance to join the current file section.
        foreach (ILoader* loader, loaders)
        {
            f.seekg(current_section); // Restore the input cursor.
            result = loader->load(f);
            
            switch(result)
            {
            case GEOC_LOADER_SUCCESS:
                // Geometry loaded successfully.
                dataParsed = true;
                if (f.eof()) done = true;
                else next_section = f.tellg();
                break;
                
            case GEOC_LOADER_UNEXPECTED_INPUT:
                // The loader found unexpected geometry.
                break;
                
            case GEOC_LOADER_ERROR:
                if (f.eof()) { f.close(); return; }
                
                printf("GEOC_LOADER_ERROR\n");
                ostringstream err;
                err << "Line: " << getLineNumber(f) << ":" << getLinePosition(f);
                err << "\nLoader failed with error code. Malformed input?";
                
                throw GEOC_EXCEPTION(err);
            }
        }
        
        if (!dataParsed)	// We were unable to parse one of the sections.
        {
            printf("NO DATA PARSED\n");
            ostringstream err;
            err << "Line: " << getLineNumber(f) << ":" << getLinePosition(f);
            err << endl << "Unable to parse file section";
            
            // Attempt to read the unparsed section header.
            f.seekg(current_section);
            string header;
            getline(f, header);
            
            if (f.good())	err << ": " << header << endl;
            else			err << "." << endl;
            
            err << "Are you missing a concrete loader?";
            
            f.close();
            throw GEOC_EXCEPTION(err);
        }
        
        f.seekg(next_section);
    }
    
    f.close();
}
