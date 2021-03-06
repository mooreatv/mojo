/***********************************************************************************************************************
/*
/*    mojo_engine.cpp / mojo_engine
/*
/*    This file implements the interface between the engine and the application.  The functions in this file are 
/*    the ones that the application calls to indirectly get its hands on the engine's data.  Most of them consist
/*    of wrappers around similar functions implemented by the engine's objects.
/*
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/***********************************************************************************************************************/


#include "stdafx.h"
#include <vector>

bool get_ip_addresses ( mojo::cArrayU * pRet );
void set_active_window_tracking ( bool );

using namespace mojo;

//======================================================================================================================
//  CODE
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
//  TEST
//----------------------------------------------------------------------------------------------------------------------
void mojo :: test ()
{
	mojo::cFileOut f ( L"temp.txt" );
	if ( 0 == f.h )
		return;
	fwprintf ( f.h, L"Test string" );
}




//----------------------------------------------------------------------------------------------------------------------
//  CLEAR PREDEFINED HOTKEY
//----------------------------------------------------------------------------------------------------------------------
bool mojo :: clear_predefined_hotkey ( const wchar_t * pName )
{
	return g_PredefinedHotkeyTable.clear( pName );
}

//----------------------------------------------------------------------------------------------------------------------
//  SET PREDEFINED HOTKEY
//----------------------------------------------------------------------------------------------------------------------
bool mojo :: set_predefined_hotkey ( const wchar_t * pName, mojo::cTrigger * pTrigger )
{
	return g_PredefinedHotkeyTable.insert ( pName, pTrigger );
}


//----------------------------------------------------------------------------------------------------------------------
//  REMOVE LAUNCH TARGET
//----------------------------------------------------------------------------------------------------------------------
void mojo :: remove_launch_target ( DWORD dwID )
{
	g_TargetMgr.remove_launch_target ( dwID );
}


//----------------------------------------------------------------------------------------------------------------------
//  SET LAUNCH TARGET
//  Adds it if it's not already there.
//----------------------------------------------------------------------------------------------------------------------
void mojo :: set_launch_target ( cTarget * p )
{
	g_TargetMgr.set_launch_target ( p );
}


//----------------------------------------------------------------------------------------------------------------------
//  START SWALLOWING KEY EVENTS
//----------------------------------------------------------------------------------------------------------------------
void mojo :: start_swallowing_key_events ( HWND hwndSwallow )
{
	g_Messenger.start_swallowing_key_events ( hwndSwallow );
}


//----------------------------------------------------------------------------------------------------------------------
//  STOP SWALLOWING KEY EVENTS
//----------------------------------------------------------------------------------------------------------------------
void mojo :: stop_swallowing_key_events ()
{
	g_Messenger.stop_swallowing_key_events ();
}


//----------------------------------------------------------------------------------------------------------------------
//  REGISTER FOR KEY EVENTS
//----------------------------------------------------------------------------------------------------------------------
void mojo::register_for_key_events   ( /* mojo::tCircBuf<WORD> * pBuf, */ HWND hNotifyMe )
{
	g_Messenger.register_for_key_events ( /* pBuf, */ hNotifyMe );
}


//----------------------------------------------------------------------------------------------------------------------
//  UNREGISTER FOR KEY EVENTS
//----------------------------------------------------------------------------------------------------------------------
void mojo::unregister_for_key_events   ( HWND hNotifyMe )
{
	g_Messenger.unregister_for_key_events ( hNotifyMe );
}


//----------------------------------------------------------------------------------------------------------------------
//  GET KEY STATE AS TRIGGER
//----------------------------------------------------------------------------------------------------------------------
void mojo :: get_key_state_as_trigger ( mojo::cTrigger * pRet )
{
	cTrigger Trig ( & g_KeyState );

	*pRet = Trig;
}


//----------------------------------------------------------------------------------------------------------------------
//  GET MACH
//----------------------------------------------------------------------------------------------------------------------
bool mojo :: get_mach ( mojo::cMach * pRet, DWORD dwHandle )
{
	return g_Machlist.get_mach ( pRet, dwHandle );	
}


//----------------------------------------------------------------------------------------------------------------------
//  SET MOUSEOVER LAYOUT
//----------------------------------------------------------------------------------------------------------------------
void mojo::set_mouseover_layout ( cMachlist * pArgList )
{
	g_Machlist.lock();
	{
		for ( cMach * pMach = g_Machlist.pHead; pMach; pMach = pMach->pNext )
		{
			cMach * pArgMach = pArgList->get_by_ip ( pMach->dwIP );

			if ( ! pArgMach )
			{
				assert(0);
				continue;
			}

			pMach->DrawPos = pArgMach->DrawPos;
			pMach->bValidDrawPos = pArgMach->bValidDrawPos;
		}
	}
	g_Machlist.unlock();

	g_Machlist.save_draw_positions_to_file ();
	g_Mouseover.set_mega_display_list ( &g_Machlist );
}



//----------------------------------------------------------------------------------------------------------------------
//  LOAD DEFAULT ENGINE SCRIBS
//----------------------------------------------------------------------------------------------------------------------
#if 0
void mojo :: load_default_engine_scribs ()
{
	assert ( g_ScribMgr.load_scribs ( g_apDefaultScribs, false ) );
}
#endif


//----------------------------------------------------------------------------------------------------------------------
//  GET TARGETS
//----------------------------------------------------------------------------------------------------------------------
void mojo :: get_targets ( cArrayTarget * pRet )
{
	g_TargetMgr.get_copy_of_targets ( pRet );
}

//----------------------------------------------------------------------------------------------------------------------
//  GET LOCAL TARGETS
//----------------------------------------------------------------------------------------------------------------------
void mojo :: get_local_targets ( cArrayTarget * pRet )
{
	g_TargetMgr.get_copy_of_local_targets ( pRet );
}


//----------------------------------------------------------------------------------------------------------------------
//  GET MACHLIST
//  Gets a copy of the real g_Machlist.
//----------------------------------------------------------------------------------------------------------------------
void mojo :: get_machlist ( mojo::cMachlist * pRet )
{
	g_Machlist.lock();
	(*pRet) = g_Machlist;
	g_Machlist.unlock();
}


//----------------------------------------------------------------------------------------------------------------------
//  GET CONNECTION STATUS
//----------------------------------------------------------------------------------------------------------------------
mojo::nConnectionStatus::eConnectionStatus mojo::get_connection_status ( DWORD dwMachHandle )
{
	DWORD dwIP = g_Machlist.handle_to_ip ( dwMachHandle );

	return (mojo::nConnectionStatus::eConnectionStatus) g_Pool.get_connection_status ( dwIP );
}


//----------------------------------------------------------------------------------------------------------------------
//  IP DWORD TO cStrW
//----------------------------------------------------------------------------------------------------------------------
void mojo :: ip_dword_to_cStrW	( cStrW * pRet, DWORD dw )
{
	wchar_t t [16];
	ip_dword_to_aw ( t, dw );
	*pRet = t;
}


//----------------------------------------------------------------------------------------------------------------------
//  IP WCHAR_T * TO DWORD
//----------------------------------------------------------------------------------------------------------------------
DWORD mojo :: ip_pw_to_dword ( const wchar_t * pAW )
{
	cStrW w = pAW;
	cStrN n ( w );
	return inet_addr ( n.cstr() );
}

//----------------------------------------------------------------------------------------------------------------------
//  GET IP ADDRESSES
//----------------------------------------------------------------------------------------------------------------------
bool mojo :: get_ip_addresses ( mojo::cArrayU * pRet )
{
	return ::get_ip_addresses ( pRet );
}


//----------------------------------------------------------------------------------------------------------------------
//  GET DLL VERSION
//----------------------------------------------------------------------------------------------------------------------
void mojo :: get_engine_version ( cVersion * pRetVersion )
{
	*pRetVersion = g_Version;	
}


/***********************************************************************************************************************
/*
/*    This file is part of Mojo.  For more information, see http://mojoware.org.
/*
/*    You may redistribute and/or modify Mojo under the terms of the GNU General Public License, 
/*    version 3, as published by the Free Software Foundation.  You should have received a copy of the 
/*    license with mojo.  If you did not, go to http://www.gnu.org.
/*     
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/*    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
/*    PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
/*    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
/*    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
/*    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/*    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/*    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
/*
/***********************************************************************************************************************/