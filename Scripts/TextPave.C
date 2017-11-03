{
TPaveText *cms = new TPaveText(0.20,0.7,0.4,0.8,"NDC");
                 //note the strict C++ syntax (not required for interactive CINT)
                 // NDC sets the coordinates relative to the dimensions of the pad
                 // useful if you might change the layout of your histos
  cms->SetFillColor(0);  //text now is black on white
  cms->SetTextSize(0.03);
  cms->SetTextAlign(12);

  TText *text = cms->AddText("CMS Preliminary");
  TText *text2= cms->AddText("#sqrt{s} = 8 TeV, 20.2 fb^{-1}");
  cms->Draw("same");       //to draw your text object
  }
