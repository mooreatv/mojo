/***********************************************************************************************************************
/*
/*    cListViewWoWs.cpp / mojo_app
/*   
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#include "stdafx.h"

using namespace mojo;

//======================================================================================================================
//  CODE
//======================================================================================================================



//----------------------------------------------------------------------------------------------------------------------
// POPULATE
//----------------------------------------------------------------------------------------------------------------------
void cListViewWoWs :: populate () // const cFigViewItemList * pListArg ) //  const cConfigItemList * pListArg )
{
	if ( pList )
	{
		delete pList;
		pList = 0;
	}

	if ( ListView_GetItemCount ( hwnd ) )
		ListView_DeleteAllItems ( hwnd );

	ListView_RemoveAllGroups ( hwnd );
	ListView_EnableGroupView ( hwnd, TRUE );

	pList = create_list ();

	insert_group ( 1, L"This computer" );

	for ( cFigViewItem * p = pList->pHead; p; p = p->pNext )
	{
		cFigWoW * w = reinterpret_cast<cFigWoW*>(p);

		if ( 1 != w->hMach )
		{
			cStrW sPC;
			sPC.f ( L"%s at %s", w->sComputerName.cstr(), w->sDottedDec.cstr() );
			insert_group ( (int) w->hMach, sPC.cstr() );
		}

		set_item ( p );
	}

	do_image_list ( pList );

	InvalidateRect ( hwnd, NULL, true );
	UpdateWindow ( hwnd );
}

//----------------------------------------------------------------------------------------------------------------------
//  SET ITEM
//----------------------------------------------------------------------------------------------------------------------
void cListViewWoWs :: set_item ( cFigViewItem * pFigViewItem )
{
	cFigWoW * pItem = reinterpret_cast<cFigWoW*> ( pFigViewItem );

	wchar_t b [100];

	LVITEM lvI;
	ZeroMemory ( &lvI, sizeof(lvI) );
	lvI.mask = LVIF_TEXT |  LVIF_PARAM | LVIF_IMAGE | LVIF_GROUPID;
	lvI.iGroupId = pItem->hMach;
	lvI.iItem = INT_MAX;
	lvI.iImage = pItem->bRunning ? 1 : 0;
	lvI.iSubItem = 0;
	lvI.lParam = (LPARAM) ( pItem->dwSerialNumber );
	lvI.pszText = const_cast<LPWSTR>( pItem->sName.cstr() );
	int iItemIndex = SendMessage ( hwnd, LVM_INSERTITEM, 0, (LPARAM) &lvI );
	ListView_SetItemText ( hwnd, iItemIndex, 1, pItem->bRunning ? L"Yes" : L"No" );
	ListView_SetItemText ( hwnd, iItemIndex, 2, (LPWSTR) pItem->sComputerName.cstr() );
	ListView_SetItemText ( hwnd, iItemIndex, 3, dword_to_string ( b, sizeof(b)/sizeof(wchar_t), (DWORD) pItem->hwnd ) );
	ListView_SetItemText ( hwnd, iItemIndex, 4, dword_to_string ( b, sizeof(b)/sizeof(wchar_t), pItem->dwProcessID ) );
	ListView_SetItemText ( hwnd, iItemIndex, 5, dword_to_string ( b, sizeof(b)/sizeof(wchar_t), pItem->dwTargetID ) );
	ListView_SetItemText ( hwnd, iItemIndex, 6, (LPWSTR) pItem->sPath.cstr() );
}


//----------------------------------------------------------------------------------------------------------------------
//  LOAD OVERLAYS INTO IMAGE LIST
//----------------------------------------------------------------------------------------------------------------------
const int * cListViewWoWs :: default_bitmap_ids ()
{
	static const int aiRet [] = { IDB_WOW_LOGO, IDB_WOW_LOGO_GREEN, 0 };

	return aiRet;
}



//----------------------------------------------------------------------------------------------------------------------
//  GET ICON SIZE
//----------------------------------------------------------------------------------------------------------------------
mojo::cPtI cListViewWoWs :: get_icon_size ()
{
	mojo::cPtI r ( 70, 69 ); // g_Settings.uWoWIconWidth, g_Settings.uWoWIconHeight );
	return r;
}

//----------------------------------------------------------------------------------------------------------------------
// LIST TO POPULATE FROM BY DEFAULT
//----------------------------------------------------------------------------------------------------------------------
void  cListViewWoWs :: create_columns ()
{
	LVCOLUMN lc;

    memset ( &lc, 0, sizeof(lc) ); 
	lc.mask= LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;    // Type of mask
	lc.pszText = L"Name";                              // First Header
	lc.cx = 130;
	SendMessage ( hwnd, LVM_INSERTCOLUMN, 0, (LPARAM) &lc );

	lc.pszText = L"Running";
	lc.cx = 60;
	SendMessage ( hwnd, LVM_INSERTCOLUMN, 1, (LPARAM) &lc );

	lc.pszText = L"Computer";
	lc.cx = 150;
	SendMessage ( hwnd, LVM_INSERTCOLUMN, 2, (LPARAM) &lc );

	lc.pszText = L"HWND";
	lc.cx = 70;
	SendMessage ( hwnd, LVM_INSERTCOLUMN, 3, (LPARAM) &lc );

	lc.pszText = L"Process ID";
	lc.cx = 70;
	SendMessage ( hwnd, LVM_INSERTCOLUMN, 4, (LPARAM) &lc );

	lc.pszText = L"Target ID";
	lc.cx = 70;
	SendMessage ( hwnd, LVM_INSERTCOLUMN, 5, (LPARAM) &lc );

	lc.pszText = L"Program file";
	lc.cx = 250;
	SendMessage ( hwnd, LVM_INSERTCOLUMN, 6, (LPARAM) &lc );
}


//----------------------------------------------------------------------------------------------------------------------
//  CREATE LIST
//----------------------------------------------------------------------------------------------------------------------
const cFigViewItemList * cListViewWoWs :: create_list ()
{
	return g_FigMgr.create_wow_list ();
	// return g_FigMgr.wow_list()->create_fig_view_item_list();

	// return 0; // g_FigMgr.get_wow_list_copy();
}


/***********************************************************************************************************************
/*
/*    This file is part of Mojo.  For more information, see http://mojoware.org.
/*
/*    You may redistribute and/or modify Mojo under the terms of the GNU General Public License, version 3, as
/*    published by the Free Software Foundation.  You should have received a copy of the license with Mojo.  If you
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
