program PAverage;

uses
  QForms,
  UFileDetails in 'UFileDetails.pas' {FileDetails},
  UFiles in 'UFiles.pas',
  ULight in 'ULight.pas',
  UMono in 'UMono.pas' {Monochromator},
  UCalibrate in 'UCalibrate.pas' {Calibrate},
  UDrift in 'UDrift.pas' {Drift},
  UCalEnergy in 'UCalEnergy.pas' {CalEnergy},
  UInspect in 'UInspect.pas' {Inspect},
  UDetails in 'UDetails.pas' {Details},
  UDDialog in 'UDDialog.pas' {DDialog},
  UWeight in 'UWeight.pas',
  UVector in 'UVector.pas',
  UConstants in 'UConstants.pas' {Constants},
  UWeightNoT in 'UWeightNoT.pas',
  UChar in '../edit/UChar.pas',
  UDraw in '../edit/UDraw.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Average';
  // Application.HelpFile := 'Average.hlp';
  Application.CreateForm(TFileDetails, FileDetails);
  Application.CreateForm(TDetails, Details);
  Application.CreateForm(TInspect, Inspect);
  Application.CreateForm(TMonochromator, Monochromator);
  Application.CreateForm(TCalibrate, Calibrate);
  Application.CreateForm(TDrift, Drift);
  Application.CreateForm(TCalEnergy, CalEnergy);
  Application.CreateForm(TDDialog, DDialog);
  Application.CreateForm(TConstants, Constants);
  Application.Run;
end.
