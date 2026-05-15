import streamlit as st
import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
from algorithms import Employee, a_star_evaluation, greedy_selection, assign_project_teams

st.set_page_config(page_title="AI HR Expert", layout="wide")

st.title("Employee performance evaluation")
st.markdown("Evaluating performance via **A\*** and team dynamics via **Graph Coloring**.")

# --- DATA ENTRY ---
with st.sidebar:
    st.header("Staff Input")
    num_emp = st.number_input("How many employees?", 2, 10, 3)
    
st.header("1. Performance Metrics")
employees = []
cols = st.columns(num_emp)

for i in range(num_emp):
    with cols[i]:
        name = st.text_input(f"Name", key=f"n{i}", value=f"Staff_{i+1}")
        p = st.slider("Productivity", 0, 100, 70, key=f"p{i}")
        e = st.slider("Years Exp", 0, 20, 5, key=f"e{i}")
        s = st.slider("Skill", 0, 100, 60, key=f"s{i}")
        t = st.slider("Teamwork", 0, 100, 50, key=f"t{i}")
        pu = st.slider("Punctuality", 0, 100, 80, key=f"pu{i}")
        employees.append(Employee(name, p, e, s, t, pu))

# --- CONFLICT MANAGEMENT ---
st.header("2. Conflict Management (Graph Coloring)")
st.info("Select pairs of employees who should NOT be on the same team (e.g., personality clashes).")
names = [e.name for e in employees]
conflicts = st.multiselect("Select pairs for conflict edges", 
                          [f"{a} & {b}" for i, a in enumerate(names) for b in names[i+1:]])

# Format conflicts for algorithm
conflict_pairs = [tuple(c.split(" & ")) for c in conflicts]

# --- EVALUATION ENGINE ---
if st.button("Run Full Expert Analysis"):
    st.divider()
    
    # A* Evaluation
    res_a = a_star_evaluation(employees)
    df = pd.DataFrame(res_a)
    
    col_a, col_b = st.columns(2)
    
    with col_a:
        st.subheader("A* Talent Ranking")
        st.dataframe(df.style.highlight_max(subset=['f'], color='#2e7d32'), use_container_width=True)
        st.caption("F-Score = Current (g) + Growth Potential (h)")

    with col_b:
        # Graph Coloring Result
        st.subheader("Optimized Team Allocation")
        teams = assign_project_teams(names, conflict_pairs)
        
        for emp, team_id in teams.items():
            st.write(f"**{emp}** → Team {team_id + 1}")
            
    # Visualizing the Conflict Graph
    st.subheader("Conflict Network Visualization")
    fig, ax = plt.subplots(figsize=(8, 3))
    G = nx.Graph()
    G.add_nodes_from(names)
    G.add_edges_from(conflict_pairs)
    
    # Color the nodes based on the algorithm's result
    node_colors = [teams[node] for node in G.nodes()]
    nx.draw(G, ax=ax, with_labels=True, node_color=node_colors, cmap=plt.cm.rainbow, node_size=1500)
    st.pyplot(fig)
    
    # FINAL EXPERT VERDICT
    best_greedy = greedy_selection(employees)
    st.success(f"### Final Expert Verdict\n"
               f"**Best for Immediate Promotion (Greedy):** {best_greedy.name}\n\n"
               f"**Best for Long-term Mentorship (A\*):** {df.iloc[0]['name']}\n\n"
               f"The team has been partitioned into {max(teams.values())+1} separate groups to avoid the selected conflicts.")