#include "Starbucks.h"
#include "Node.h"

class reidta3Starbucks : public Starbucks {
	public:
	
	Node* root;

	reidta3Starbucks();

	virtual void build(Entry* c, int n);
	
	virtual Entry* getNearest(double x, double y);
};