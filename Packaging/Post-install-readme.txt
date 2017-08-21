Information for Average version 2.0.6 beta
==========================================

(This version dated Apr 2nd, 2007)

Average is a program for averaging data from multi-element detectors
and/or multiple EXAFS/XANES scans.  Users of this version are encouraged,
nay entreated, to test it hard, particularly anything listed in the
"untested" section below.  If any features from previous versions which are
missing from this version are needed, please let jrh@anbf2.kek.jp know!

Changes from previous version (1.2)
-----------------------------------

The previous version (1.2) never left beta status due to a number of
unpleasant user interface bugs.  Producing the present version involved
rewriting the user interface code from Delphi to wxWidgets.  In the process,
a large number of small bugs were fixed and a few small enhancements to the
interface included.  Specific changes include:

* The correct number of channel lights is always displayed

* The plotting window allows zooming by clicking and dragging the left mouse

* The calibration line is moved by dragging with the right mouse

* Crashes when choosing and then unselecting use of a foil for calibration
  have been fixed

* All plots have very visible solid lines

* A data module for PF-AR NW10A is included - please test this

Some functionality has yet to be updated, including:

* No popup menu in the plot window for changing weighting and colour schemes

* No facility to re-read averaged files

Changes from version 2.0 beta
------------------------------

* Fixed spurious extra fluorescence channel light
* Transmission data is now dealt with properly (but have not checked numerical correctness yet)
* Data input module for PF-AR beamline NW10A now included

Changes from version 2.0.1 beta
--------------------------------

* Fix for incorrect offset calculation in NW10A module
* Changed colour schemes for data displays for improved visibility
* Removed points in data plots due to user complaints
* (This is the biggie) Calibration is now done on an angular scale instead of energy scale.
   Those who want the old behaviour can check the "Use energy" box in the Calibration window
* Added big button on main window to display per-file information
* The per-file information display now allows changing of mono d spacing, calibration value, and E0.  Note
  that you can change deadtime to whatever you like, but it has no effect on the data (yet).
* Source-level fixes to allow compilation on MacOSX (now possible).  If you want a MacOSX package,
  contact me.

Changes from version 2.0.2 beta
-------------------------------

* Fix for scaling bug in XAS display

Changes from version 2.0.3 beta
-------------------------------

* Fixed out-by-one error in array access during file writes

Changes from version 2.0.4 beta
-------------------------------

* Fixed harmless premature call to set status bar information in Inspect window
* Fixed potentially nasty foil calibration bug
* Fixed crashing when reopening calibrate window
* Preparations under the hood for excluding regions of data

Changes from version 2.0.5 beta
-------------------------------

* Added unzoom button
* Fixed annoying layout bug

Please send any and all feedback to James Hester: jrh@anbf2.kek.jp