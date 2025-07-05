//Quero achar um ponto com a distancia d do ponto (x,y), 
//na reta construida com o ponto (x,y) e (x2,y2)
//Complexidade: O(1)
pair<double, double> projeção(double x, double y, double x2, double y2, double d) {
    double dx = x2 - x;
    double dy = y2 - y;
    double len = sqrt(dx*dx + dy*dy);
    double ux = dx / len;
    double uy = dy / len;
    return {x + ux * d, y + uy * d};
}

//Projetar ponto na reta P(x0,y0) na reta formada pelos pontos (x1,y1) e (x2,y2)
//Complexidade: O(1)
pair<double, double> projecao_na_reta(double x0, double y0,double x1, double y1,double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double apx = x0 - x1;
    double apy = y0 - y1;

    double dot = apx * dx + apy * dy;
    double len_sq = dx * dx + dy * dy;

    double t = dot / len_sq;

    double proj_x = x1 + t * dx;
    double proj_y = y1 + t * dy;

    return {proj_x, proj_y};
}
