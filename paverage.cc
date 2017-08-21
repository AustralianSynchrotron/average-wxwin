#include "paverage.h"

IMPLEMENT_APP(PaverageApp)

bool PaverageApp::OnInit()
{
wxFileConfig * config_data;   //Load module, CWD information
wxString module_names;   // All of the module names
wxStandardPaths * stdpaths;  //Where to find config files
wxString local_config,global_config;
long dummy;
wxString cwd;
bool bCont;
wxString this_module;
char * modlist;
FileDetails *MainWin = new FileDetails(_("Average"),wxDefaultPosition,
                     wxSize(300,200));

MainWin->Show(TRUE);
SetTopWindow(MainWin);
stdpaths = new wxStandardPaths();
global_config = stdpaths->GetDataDir();
local_config = stdpaths->GetUserDataDir();
// We don't use escape characters so that we can use INNO setup on Windows to
// write in the locations of the loadable DLLs
config_data = new wxFileConfig(_("XFIT"),
		                 _(""),
				 _("XFIT.INI"),
		                 _(""),
				 wxCONFIG_USE_LOCAL_FILE|wxCONFIG_USE_NO_ESCAPE_CHARACTERS);
//Get a list of modules
config_data->SetPath(_("data modules"));
module_names = _("");
bCont = config_data->GetFirstEntry(this_module,dummy);
while(bCont)
{
	module_names+=(config_data->Read(this_module));
	module_names+=_(";");
	bCont = config_data->GetNextEntry(this_module,dummy);
}
//Now pass this to our DLL
modlist = (char *) malloc((module_names.Len()+1)*sizeof(char));
sprintf(modlist,"%s", (const char *) module_names.mb_str());
Command (ADD_MODULES,modlist);
//Set current directory
config_data->SetPath(_("/Average"));
cwd = _("");
if(config_data->Read(_("CurrentDirectory"),&cwd))
{
	wxSetWorkingDirectory(cwd);
}
return TRUE;
}
