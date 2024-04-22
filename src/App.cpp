// WXWIDGETS AUTOMATICALLY DEALLOCATES ALL DYNAMICALLY ALLOCATED MEMORY, NO NEED FOR DESTRUCTOR
#include "App.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Cosmic Collision");
	mainFrame->SetClientSize(900, 700);
	mainFrame->Center();
	mainFrame->Show();
	//MainFrame* resultsFrame = new MainFrame("Cosmic Collision Results");
	//resultsFrame->SetClientSize(900, 700);
	//mainFrame->AddChild(resultsFrame);

	return true;
}
