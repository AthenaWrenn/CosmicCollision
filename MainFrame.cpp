#include "MainFrame.h"
#include <wx/wx.h>

// Constructor for the window, creates three objects and a status bar (functions similarly to a console)
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	createControls();
	CreateStatusBar();
}


void MainFrame::OnSearchButtonClicked(wxCommandEvent& evt) {
	//Generates the results using the backend created by Joseph and Athena
	vector<Node> results = algorithm.algorithm(wxAtoi(this->yearBox->GetValue()), wxAtof(this->latitudeBox->GetValue()), wxAtof(this->longitudeBox->GetValue()), wxAtof(this->sizeBox->GetValue()), wxAtoi(this->yearRankBox->GetValue()), wxAtoi(this->locationRankBox->GetValue()), wxAtoi(this->sizeRankBox->GetValue()));
	
	//Hides the main panel and shows the new panel (screen change)
	delete mainPanel;
	this->resultsPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, this->GetClientSize());
	this->resultsPanel->Show();

	//Generates the list of meteors for the user
	this->resultsText = new wxStaticText(resultsPanel, wxID_ANY, "Closest Metorites:", wxPoint(300, 50), wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	this->resultsText->SetFont(this->GetFont().Scale(3));
	wxArrayString resArr;
	int rankCount = 1;

	this->backButton = new wxButton(resultsPanel, wxID_ANY, "Return to Search Menu", wxPoint(450, 525));
	this->backButton->Bind(wxEVT_BUTTON, &MainFrame::OnBackButtonClicked, this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);


	//Checks if there were results output. If not, then an appropriate message is displayed
	if (!results.empty() && (int)results[0].getScore() != 0) {
		
		//Loops through every meteor and outputs its data
		for (auto& meteor : results) {
			map<string, string> info = meteor.getNodeInfo();
			string meteorInfo = to_string(rankCount) + ") Score: " + info["Score"] + ", " +
								"Name: " + info["Name"] + ", " +
								"ID: " + info["ID"] + ", " +
								"Class: " + info["Class"] + ", " +
								"Mass: " +	info["Mass"] + ", " +
								"Year: " + info["Year"] + ", " +
								"Latitude: " + info["Latitude"] + ", " +
								"Longitude: " + info["Longitude"];
			resArr.Add(meteorInfo);
			resArr.Add("");
			rankCount++;
		}

		this->resultsList = new wxListBox(resultsPanel, wxID_ANY, wxPoint(25, 200), wxDefaultSize, resArr);

		wxLogStatus("Results run");
	
	} else {
		resArr.Add("NO SIMILAR METEORS FOUND");
		this->resultsList = new wxListBox(resultsPanel, wxID_ANY, wxPoint(325, 200), wxSize(100, 100), resArr);
		resultsList->SetFont(this->GetFont().Scale(1.25));
		resultsList->Fit();
		
		sizer->AddStretchSpacer();
		sizer->Add(resultsList, 0, wxALIGN_CENTER_HORIZONTAL);
		sizer->AddStretchSpacer();

		resultsPanel->SetSizer(sizer);
		wxLogStatus("No results!");
	}
}

void MainFrame::OnBackButtonClicked(wxCommandEvent& evt) {
	delete resultsPanel;
	createControls();
}

void MainFrame::createControls() {
	this->mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, this->GetClientSize(), wxWANTS_CHARS);

	this->frameTitle = new wxStaticText(mainPanel, wxID_ANY, "Meteorite Landing Finder", wxPoint(275, 50), wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	this->frameTitle->SetFont(this->GetFont().Scale(2));
	this->titleDesc = new wxStaticText(mainPanel, wxID_ANY, "Please enter your specifications:", wxPoint(300, 150), wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);

	this->yearBox = new wxTextCtrl(mainPanel, wxID_ANY, "Specify Year", wxPoint(150, 225), wxSize(200, -1));
	this->latitudeBox = new wxTextCtrl(mainPanel, wxID_ANY, "Specify Latitude", wxPoint(150, 325), wxSize(200, -1));
	this->longitudeBox = new wxTextCtrl(mainPanel, wxID_ANY, "Specify Longitude", wxPoint(150, 425), wxSize(200, -1));
	this->sizeBox = new wxTextCtrl(mainPanel, wxID_ANY, "Specify Size", wxPoint(150, 525), wxSize(200, -1));


	this->yearRankBox = new wxTextCtrl(mainPanel, wxID_ANY, "Rank importance of year(1-4):", wxPoint(450, 225), wxSize(200, -1));
	this->locationRankBox = new wxTextCtrl(mainPanel, wxID_ANY, "Rank importance of location(1-4):", wxPoint(450, 325), wxSize(200, -1));
	this->sizeRankBox = new wxTextCtrl(mainPanel, wxID_ANY, "Rank importance of size(1-4):", wxPoint(450, 425), wxSize(200, -1));
	this->enterButton = new wxButton(mainPanel, wxID_ANY, "Find meteorites!", wxPoint(450, 525));
	
	this->enterButton->Bind(wxEVT_BUTTON, &MainFrame::OnSearchButtonClicked, this);
}

