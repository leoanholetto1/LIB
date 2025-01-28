struct Rect{
    ll x1,y1,x2,y2;
    Rect(){}
    Rect(ll _x1,ll _y1,ll _x2,ll _y2){
        x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;
    }
    ll area(){
        return (x2-x1)*(y2-y1);
    }
    Rect intersect(const Rect &b){
        Rect c;
        c.x1 = max(x1,b.x1);
        c.y1 = max(y1,b.y1);
        c.x2 = min(x2,b.x2);
        c.y2 = min(y2,b.y2);
        return c;
    }
    bool isIntersect(const Rect &b){
        Rect c = intersect(b);
        if(c.x1 > c.x2 or c.y1 > c.y2) return 0;
        return 1;
    }
    ll areaIntersect(const Rect &b){
        if(isIntersect(b)){
            Rect c = intersect(b);
            return c.area();
        }
        else return 0;
    }
    double diagonal(){
        return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    }
    pair<double,double> centro(){
        return {x1+(x2-x1)/2.0,y1+(y2-y1)/2.0};
    }
	Rect quadradoMin(const Rect &b){
		ll x = min(x1,b.x1);
		ll y = min(y1,b.y1);
		ll xx = max(x2,b.x2);
		ll yy = max(y2,b.y2);
		return {x,y,xx,yy};
	}
};