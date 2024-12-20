//Complexidade: O(n + m)
int timer = 0;
void euler_tour(int at, int prev) {
	start[at] = timer++;
	for (int n : adj[at]) {
		if (n != prev) { euler_tour(n, at); }
	}
	end[at] = timer;
}