#ifndef COMMANDER_STATUSPANEL_H
#define COMMANDER_STATUSPANEL_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Panel.h>

typedef enum
{
	TYPE_UNKNOWN = 0,
	TYPE_INFO,			// More invloved, with box and grayed background
						// If it has a \n, the lines after the first aren't as large
	TYPE_INFONOTITLE,	// Don't treat first line with a \n specially
	TYPE_HINT			// Single line flyover
} STATUSTYPE;

namespace vgui
{
	class LineBorder;
}

#ifdef IMPLEMENT_ME
class CBaseTechnology;
#endif

//-----------------------------------------------------------------------------
// Purpose: The status line appears along the bottom of the screen and shows
//  tooltip style help
//-----------------------------------------------------------------------------
class CCommanderStatusPanel : public vgui::Panel
{
public:
	typedef vgui::Panel BaseClass;
	//DECLARE_CLASS_SIMPLE(CCommanderStatusPanel,vgui::Panel);

	enum { MAX_STATUS_TEXT = 4096 };

							CCommanderStatusPanel( void );
	virtual					~CCommanderStatusPanel( void );

	virtual void			ApplySchemeSettings(vgui::IScheme *pScheme);

	virtual void			Paint();
	virtual void			PaintBackground();
	virtual void			OnTick();

	// Set status text
	virtual void			SetText( STATUSTYPE type, const char *fmt, ... );
#ifdef IMPLEMENT_ME
	virtual void			SetTechnology( CBaseTechnology *technology );
#endif
	virtual void			Clear();

	virtual void			SetLeftBottom( int l, int b );

private:
	void					RecomputeBounds( void );
	void					InternalClear();

private:
	float					m_flCurrentAlpha;
	float					m_flGoalAlpha;

	int						m_nLeftEdge;
	int						m_nBottomEdge;

	vgui::HFont				m_hFont;
	vgui::HFont				m_hFontText;
	vgui::LineBorder		*m_pBorder;

	// Position of the first '\n' character
	char					m_nTitlePos;


	STATUSTYPE				m_Type;
	char					m_szText[ MAX_STATUS_TEXT ];
	bool					m_bShowTechnology;
#ifdef IMPLEMENT_ME
	CBaseTechnology			*m_pTechnology;
#endif
};

void StatusCreate( vgui::Panel *parent, int treetoprow );
void StatusDestroy( void );
void StatusSetTopRow( int treetoprow );

void StatusPrint( STATUSTYPE type, const char *fmt, ... );
#ifdef IMPLEMENT_ME
void StatusTechnology( CBaseTechnology *technology );
#endif
void StatusClear( void );

#endif // COMMANDER_STATUSPANEL_H
