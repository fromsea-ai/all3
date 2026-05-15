import heapq
import networkx as nx

class Employee:
    def __init__(self, name, productivity, experience, skill, teamwork, punctuality):
        self.name = name
        self.productivity = productivity
        self.experience = experience
        self.skill = skill
        self.teamwork = teamwork
        self.punctuality = punctuality

    def get_gn(self):
        """g(n): Current performance score."""
        return (0.30 * self.productivity + 0.20 * (self.experience * 5) + 
                0.20 * self.skill + 0.15 * self.teamwork + 0.15 * self.punctuality)

    def get_hn(self):
        """h(n): Heuristic - Potential (Low exp + High skill = High Potential)."""
        return ((100 - (self.experience * 5)) * 0.1) + (self.skill * 0.05)

    def f_score(self):
        """f(n) = g(n) + h(n)"""
        return self.get_gn() + self.get_hn()

# --- A* Search ---
def a_star_evaluation(employees):
    priority_queue = []
    for emp in employees:
        heapq.heappush(priority_queue, (-emp.f_score(), emp))
    
    ranked = []
    while priority_queue:
        neg_f, emp = heapq.heappop(priority_queue)
        ranked.append({"name": emp.name, "f": round(-neg_f, 2), "g": round(emp.get_gn(), 2), "h": round(emp.get_hn(), 2)})
    return ranked

# --- Greedy Selection ---
def greedy_selection(employees):
    if not employees: return None
    return max(employees, key=lambda e: e.get_gn())

# --- Graph Coloring (New) ---
def assign_project_teams(employee_names, conflicts):
    """
    Ensures that employees with a 'conflict' (edge) are placed in different teams (colors).
    """
    G = nx.Graph()
    G.add_nodes_from(employee_names)
    G.add_edges_from(conflicts)
    
    # Greedy coloring assigns integers (0, 1, 2...) representing Team IDs
    coloring = nx.coloring.greedy_color(G, strategy="largest_first")
    return coloring