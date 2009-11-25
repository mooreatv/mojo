/***********************************************************************************************************************
/*
/*    cDlgLicense.h / mojo_app
/*
/*    Wrapper for "License agreement" dialog box.
/*   
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#pragma once

#include "cDlg.h"

//----------------------------------------------------------------------------------------------------------------------
//  CLASS cDlg
//----------------------------------------------------------------------------------------------------------------------
class cDlgLicense : public cDlgModal
{
public:
	virtual DialogProc * dialog_proc () { return dialog_proc; }
	static DialogProc dialog_proc;
	virtual int idd () { return IDD_LICENSE; }
	void save ();
	void wm_scroll ( WPARAM );
	void wm_init ( HWND hwnd );
	void set_sizes ();
	int draw_text ( HWND hwnd, bool bDraw = true ); // if false, returns height
	void wm_mousewheel ( WPARAM wParam );
	void wm_paint ();

private:

	int iEditCtrlDimY ;
	int iScrollRange;
	bool thumb_is_at_bottom ();
	bool scroll_bar_is_visible ();
	void load_text ();

	cWin Accept;
	cWin Decline;
	// cWin Save;
	cWin Text0;
	cWin Text1;
	cWin Text2;
	cWin Text3;

};


/***********************************************************************************************************************
/*
/*    This file is part of Mojo.  For more information, see http://mojoware.org.
/*
/*    You may redistribute and/or modify Mojo under the terms of the GNU General Public License, version 3, as
/*    published by the Free Software Foundation.  You should have received a copy of the license with mojo.  If you
/*    did not, go to http://www.gnu.org.
/* 
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
/*    NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
/*    IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
/*    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
/*    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
/*    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/*    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
/*
/***********************************************************************************************************************/