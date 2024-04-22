#pragma once
#include <wx/wx.h>
#include <vector>
#include "Backend.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);

private:
	// Outlines lambdas which are used to define what occurs during given events
	void OnSearchButtonClicked(wxCommandEvent& evt);
	void OnBackButtonClicked(wxCommandEvent& evt);

	void createControls();

	Backend algorithm;

	wxStaticText* frameTitle;
	wxStaticText* titleDesc;

	wxTextCtrl* yearBox;
	wxTextCtrl* latitudeBox;
	wxTextCtrl* longitudeBox;
	wxTextCtrl* sizeBox;

	wxTextCtrl* yearRankBox;
	wxTextCtrl* locationRankBox;
	wxTextCtrl* sizeRankBox;
	wxButton* enterButton;

	std::vector<Node> results;

	wxStaticText* resultsText;
	wxListBox* resultsList;
	wxButton* backButton;

	wxPanel* mainPanel;
	wxPanel* resultsPanel;

	wxString year;
	wxString latitude;
	wxString longitude;
	wxString size;
	wxString yearRank;
	wxString locationRank;
	wxString sizeRank;
};
