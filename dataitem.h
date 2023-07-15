#pragma once

#include "treeitem.h"

class PieceItem : public TreeItem {
  public:
    virtual QString getTitle() { return ""; }
    virtual QString getDescription() { return ""; }
    virtual QString getTag() { return ""; }
};
class VideoItem : public TreeItem {
  public:
    virtual QString getTitle() { return ""; }
    virtual QString getDescription() { return ""; }
    virtual QString getTag() { return ""; }
};
class ActorItem : public TreeItem {
  public:
    virtual QString getTitle() { return ""; }
    virtual QString getDescription() { return ""; }
    virtual QString getTag() { return ""; }
};
