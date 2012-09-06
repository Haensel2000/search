#ifndef GRAPH_UTILS_H_
#define GRAPH_UTILS_H_

template <class Graph>
double cost(Graph g, const vector<typename Graph::StateType>& path)
{
	typedef typename Graph::StateType S;

	double result = 0.0;
	if (path.size() > 0)
	{
		typename vector<S>::const_iterator prev = path.begin();
		for (typename vector<S>::const_iterator i = prev+1; i != path.end(); ++i)
		{
			result += g.cost(*prev, *i);
			prev = i;
		}
	}
	return result;
}

#endif