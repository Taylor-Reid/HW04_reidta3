#include "Census.h"
#include "cNode.h"

class reidta3Census : public Census {
	public:
	
	cNode* root;

	reidta3Census();

	virtual void build(cEntry* c, int n);
	
	virtual cEntry* getNearest(double x, double y);
};