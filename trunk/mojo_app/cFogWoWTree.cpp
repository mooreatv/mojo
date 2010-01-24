/***********************************************************************************************************************
/*
/*    cFogWoWTree.cpp / mojo_app
/*   
/*    Copyright 2010 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#include "stdafx.h"
#include "cFog_define.h"


//======================================================================================================================
//  DATA
//======================================================================================================================

cFogTree::sEntry cFogWoWTree::aTable [] =
{
	{ 0, 0, 0 }
};


//======================================================================================================================
//  PROTOTYPES
//======================================================================================================================


//======================================================================================================================
//  CODE
//======================================================================================================================

#if 0
//----------------------------------------------------------------------------------------------------------------------
//  FIND TARGET
//----------------------------------------------------------------------------------------------------------------------
cFogWoW * cFogWoWTree :: find_target ( mojo::cTarget * a )
{
	for ( cTree * p = pRight; p; p = p->pRight )
	{

		cFogWoW * w = reinterpret_cast < cFogWoW* > ( p );

		if ( a->bLaunchByMojo )
		{
			if ( w->hMach == a->hMach && w->dwTargetID == a->dwID )
				return w;
		}

		else
		{
			if ( a->hwnd == w->hwnd && a->hMach == w->hMach && a->dwProcessID == w->dwProcessID )
				return w;
		}
	}

	return NULL;
}


//----------------------------------------------------------------------------------------------------------------------
//  GET BY HWND
//----------------------------------------------------------------------------------------------------------------------
cFogWoW * cFogWoWTree :: get_by_hwnd ( HWND hwnd ) const
{
	for ( cTree * p = pRight; p; p = p->pRight )
	{
		cFogWoW * w = reinterpret_cast < cFogWoW* > ( p );

		if ( w->hwnd == hwnd )
			return w;
	}

	return NULL;
}


//----------------------------------------------------------------------------------------------------------------------
//  FIND TARGET 
//----------------------------------------------------------------------------------------------------------------------
cFogWoW * cFogWoWTree :: find_target ( DWORD hMach, HWND hwnd, DWORD dwProcessID ) const
{
	for ( cTree * p = pRight; p; p = p->pRight )
	{
		cFogWoW * w = reinterpret_cast < cFogWoW* > ( p );

		if ( hwnd == w->hwnd && hMach == w->hMach && dwProcessID == w->dwProcessID )
			return w;
	}

	return NULL;
}


//----------------------------------------------------------------------------------------------------------------------
//  SET FROM XML
//----------------------------------------------------------------------------------------------------------------------
void cFogWoWTree :: set_from_xml ( void * pvDest, const wchar_t * pTxt ) const
{
	cFogRoot * pRoot = reinterpret_cast<cFogRoot*>(pvDest);

	cFogWoWTree * pWoWTree = pRoot->get_wow_tree();

	if ( ! pWoWTree )
	{
		pWoWTree = new cFogWoWTree;
		pRoot->append_left ( pWoWTree );
	}

	pWoWTree->cFog::set_from_xml ( pWoWTree, pTxt );
}


//----------------------------------------------------------------------------------------------------------------------
//  WRITE TO XML
//  Writes the whole element
//----------------------------------------------------------------------------------------------------------------------
void cFogWoWTree :: write_to_xml ( cStrW * pRet, void * pObject, const wchar_t * pTagName ) const
{
	pRet; pObject; pTagName;

	cFogRoot * pRoot = reinterpret_cast<cFogRoot*>(pObject);

	cFogWoWTree * p = (cFogWoWTree *) pRoot->get_by_typeid ( typeid ( cFogWoWTree::Default ) . raw_name() );

	if ( ! p )
		return;

	xml_write_start_tag ( pRet, pTagName );
	*pRet += L'\n';

	for ( cTree * pTree = p->pRight; pTree; pTree = pTree->pRight )
	{
		cFogWoW * pWoW = reinterpret_cast<cFogWoW*>(pTree);

		if ( true == pWoW->bLaunchByMojo )
			pWoW->write_to_xml ( pRet, pWoW, table()->pwTag );
	}

	xml_write_end_tag ( pRet, pTagName );
	*pRet += L'\n';
}

#endif

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