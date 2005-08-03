/*
 *  copyright (C) 2005
 *  Dimitri Ognibene <ognibened @yahoo.it>
 */

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef AUTOLAYOUTGRAPHVIZAUTOLAYOUTER_H
#define AUTOLAYOUTGRAPHVIZAUTOLAYOUTER_H
#include "baseinclude.h"
#include "autolayouteradapter.h"
#include "graphvizgraph.h"

namespace Autolayout
{

/**
@author 
*/
class GraphvizAutolayouter : virtual public Autolayout::AutolayouterAdapter
{
public:
    GraphvizAutolayouter();


    virtual void setCompressShapes(bool b);

    virtual void setCenterDiagram(bool b);

    virtual void setShapeSeparation(int i);

    virtual ~GraphvizAutolayouter();

protected:
    virtual Graph* getGraph(){if (!gg) gg=new GraphvizGraph(); return gg;}

    virtual void run()=0;
    GraphvizGraph* gg;

};

}

#endif
