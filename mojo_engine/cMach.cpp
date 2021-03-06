/***********************************************************************************************************************
/*
/*    cMach.cpp / mojo_engine
/*   
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#include "stdafx.h"

using namespace mojo;

//----------------------------------------------------------------------------------------------------------------------
//  MAKE PRETTY NAME
//----------------------------------------------------------------------------------------------------------------------
const wchar_t * cMach :: make_pretty_name ( mojo::cStrW * pRet )
{
	if ( 1 == dwSerialNumber )
		*pRet = L"This computer";

	else if ( this->sDottedDec.len() )
		pRet->f ( L"%s on %s", sName.cstr(), sDottedDec.cstr() );

	else
		*pRet = sDottedDec.cstr();

	return pRet->cstr();
}


//----------------------------------------------------------------------------------------------------------------------
//  OPERATOR =
//----------------------------------------------------------------------------------------------------------------------
mojo::cMach & mojo::cMach::operator= ( const mojo::cMach & rh )
{
	dwSerialNumber	= rh.dwSerialNumber;
	bThisPC 		= rh.bThisPC;
	DrawPos			= rh.DrawPos;
	DisplayList		= rh.DisplayList;
	bValidDrawPos	= rh.bValidDrawPos;
	dwIP			= rh.dwIP;
	sDottedDec		= rh.sDottedDec;
	sName			= rh.sName;

	return * this;

}

//----------------------------------------------------------------------------------------------------------------------
//  COPY CONSTRUCTOR
//----------------------------------------------------------------------------------------------------------------------
mojo::cMach::cMach ( const mojo::cMach & rh ) :	    pNext			( 0 ),
													pPrev			( 0 ),
													dwSerialNumber	( rh.dwSerialNumber ),
													bThisPC 		( rh.bThisPC ),
													DrawPos 		( rh.DrawPos ),
													DisplayList 	( rh.DisplayList ),
													bValidDrawPos	( rh.bValidDrawPos ),
													dwIP			( rh.dwIP ),
													sDottedDec		( rh.sDottedDec ),
													sName			( rh.sName )
{
	InitializeCriticalSectionAndSpinCount(&this->cs, 4000 );
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