/*
 * Copyright 2003, Heikki Suhonen
 * Copyright 2009, Karsten Heimrich
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Heikki Suhonen <heikki.suhonen@gmail.com>
 *		Karsten Heimrich <host.haiku@gmx.de>
 *
 */
#ifndef DRAWING_TOOL_H
#define	DRAWING_TOOL_H

#include "ImageView.h"
#include "Tools.h"
#include "ToolScript.h"


class BFile;


#define	HS_MAX_TOOL_NAME_LENGTH		50
#define OPTION_CHANGED				'Opcg'


// this is a base class that specific tool-classes will be based on
class DrawingTool {
public:
							DrawingTool(const char *tool_name, int32 tool_type);
	virtual					~DrawingTool();

	virtual	int32			UseToolWithScript(ToolScript*, BBitmap*);
	virtual	ToolScript*		UseTool(ImageView*, uint32, BPoint, BPoint);

	virtual	BView*			makeConfigView();
	virtual	void			UpdateConfigView(BView*) {}

	inline	int32			Options() { return options; }
	virtual	void			SetOption(int32 option, int32 value,
								BHandler* source = NULL);

	virtual	int32			GetCurrentValue(int32 option);

	inline	const char*		GetName() const { return name; }
	inline	const int32		GetType() const { return type; }

	// these functions read and write tool's settings to a file
	virtual status_t		readSettings(BFile &file,bool is_little_endian);
	virtual	status_t		writeSettings(BFile &file);

			BRect			LastUpdatedRect();

	virtual	const void*		ToolCursor() const;
	virtual	const char*		HelpString(bool isInUse) const;

protected:
			char			name[HS_MAX_TOOL_NAME_LENGTH];
			int32			type;

			int32			options;
			int32			number_of_options;

			// this struct contains the tool's settings
			tool_settings	settings;

			// The UseTool-function should set this region. Before starting the
			// UseTool-function should wait for this region to become empty
			BRect			last_updated_rect;
};


class DrawingToolConfigView : public BView {
public:
							DrawingToolConfigView(DrawingTool* newTool);
	virtual					~DrawingToolConfigView();

	virtual	void			AttachedToWindow();
	virtual	void			MessageReceived(BMessage* message);

protected:
			DrawingTool*	tool;
};

#endif
