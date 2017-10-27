Is is suffucient to only attach our extended vertex to two of the members of a cycle?
Since every cycle will have a maximum degree of two?

while(std::cin>>G)
{
	cycleList=getCycles(G)
	for(auto cycle:cycleList)
	{
		if(!isCycleExtendable(cycle))
		{
			printGraph(G)
		}
	}
}

findNewCycle(G,path,size,i,j)
{
	
}

isCycleExtendable(cycle)
{
	for path in cycleList
		for i = 0; i<G.size()-1
			for j=i+1;G.size()
				makeConnection(G[G.size()-1],G[i],G[j] 
				findNewCycle(G,path,G.size()-1,i,j)
}

DFS(G,visited,cyclelist*,v,vCur,path)
{
	visited[vCur] = true;
	path.union(vCur);
	if(v==vCur)
	{
		cycleList.add({path});
	}
	for(connections in G[vCur])
	{
		if(visited[connection])
		{
			DFS(G,visited,cycleList,V,connection,path)
		}
	}
	return

}

getCycles(G)
{
	for v in G
		for connection in G[v]
			DFS(~,V,connections,~)
		removeFromGraph(G,V);

}
