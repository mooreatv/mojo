/***********************************************************************************************************************
/*
/*    cTarget.h
/*   
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#pragma once

//======================================================================================================================
//  CLASS
//======================================================================================================================
namespace mojo
{

class MOJO_ENGINE_API cTarget
{
public:

	cTarget () : pPrev(0), pNext(0), hwnd(0) {}
	cTarget ( const cTarget & p ) : hwnd ( p.hwnd ), sPath ( p.sPath ), pPrev(0), pNext(0) {}

	DWORD hMachHandle;
	HWND hwnd;
	mojo::cStrW sPath;
	cTarget * pPrev;
	cTarget * pNext;
};


//----------------------------------------------------------------------------------------------------------------------
//  CLASS ARRAY OF TARGETS
//----------------------------------------------------------------------------------------------------------------------
class MOJO_ENGINE_API cArrayTarget : public tArray<cTarget>
{
public:

	typedef tArray<cTarget> B; // base
	cArrayTarget( unsigned a ) : B ( a ) {}
	cArrayTarget() {}
};

} // namespace



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