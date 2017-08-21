# Makefile for wxwidgets version of Average

project_objects = FileDetails.o paverage.o tlight.o tfile.o TInspect.o \
                  TWeightThread.o TConstants.o TCalibrate.o TCalEnergy.o \
		  TDrift.o TDetails.o TMono.o

project_name = wxpaverage

# These flags derived from wx-config command for wxwidgets

LDFLAGS = -L../unixclibrary-average-wxwin \
          -pthread   -lwx_gtk2u_xrc-2.6 -lwx_gtk2u_qa-2.6 -lwx_gtk2u_html-2.6 \
          -lwx_gtk2u_adv-2.6 -lwx_gtk2u_core-2.6 -lwx_baseu_xml-2.6 \
          -lwx_baseu_net-2.6 -lwx_baseu-2.6 \
          -laverage-1.4 \
		  -lwx_gtk2u_plotctrl-2.6 \
		  -lwx_gtk2u_wxthings-2.6

CXXFLAGS = -I/usr/lib/wx/include/gtk2-unicode-release-2.6 \
           -I/usr/include/wx-2.6 \
		   -I/usr/local/src/wxcode/wxplotctrl/include \
		   -I/usr/local/src/wxcode/wxthings/include \
           -DGTK_NO_CHECK_CASTS -D__WXGTK__ -D_FILE_OFFSET_BITS=64 \
           -D_LARGE_FILES -D_LARGEFILE_SOURCE=1 -DNO_GCC_PRAGMA \
           -DwxUSE_UNICODE
           

# This is for the dll data structure definitions

XTRA_INCLUDES = -I../unixclibrary-average-wxwin

%.o: %.cpp %.h
	$(CXX) -g -c $(CXXFLAGS) $(XTRA_INCLUDES) $< -o $@ 
#
%.o: %.cc %.h
	$(CXX) -g -c $(CXXFLAGS) $(XTRA_INCLUDES) $< -o $@ 
#
project: $(project_objects)
	gcc -g -o $(project_name) $(LDFLAGS) $?

clean: 
	rm $(project_objects)
