#include "Starbucks.h"

class reidta3Starbucks : public Starbucks {
	public:

	Node* sentinel;
	
	reidta3Starbucks();

	virtual void build(Entry* c, int n);
	
	virtual Entry* getNearest(double x, double y);
};