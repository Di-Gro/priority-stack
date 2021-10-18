#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

// P - количество приоритетов
// Push(): log(P) + P
// Pop(): O(1)

template <typename T>
class PriorityStack {

private:
	class Node {
	public:
		int priority;
		T value;

		Node(int p, T v) : priority(p), value(v) {}
	};

	using NodeIterator = typename list<Node>::iterator;

	class Key {
	public:
		int priority;
		NodeIterator node;

		Key(int p) : priority(p) {}
		Key(int p, NodeIterator n) : priority(p), node(n) {}
	};

	vector<Key> m_keys;
	list<Node> m_nodes;

public:

	void Push(int priority, T value) {
		Node node(priority, value);

		// Среди nodes приоритетные вначале
		// Среди keys приоритетные вконце

		static auto comp = [](const Key & a, const Key & b) {
			return a.priority < b.priority;
		};

		auto keyIt = lower_bound(m_keys.rbegin(), m_keys.rend(), Key(priority), comp);

		if (keyIt == m_keys.rend()) {
			m_nodes.push_back(node);
			m_keys.insert(keyIt.base(), Key(priority, --m_nodes.end()));
			return;
		}
		if (keyIt->priority == priority) {
			auto nodeIt = m_nodes.insert(keyIt->node, node);
			keyIt->node = nodeIt;
			return;
		}
		auto nodeIt = m_nodes.insert(keyIt->node, node);
		m_keys.insert(keyIt.base(), Key(priority, nodeIt));
	};

	T Pop() {
		if (IsEmpty())
			throw exception("Pop() called on empty stack");

		auto & key = m_keys[m_keys.size() - 1];
		auto nodeIt = key.node;
		auto nextNodeIt = nodeIt;
		nextNodeIt++;

		if (nextNodeIt == m_nodes.end() || nextNodeIt->priority != nodeIt->priority)
			m_keys.pop_back();
		else
			key.node = nextNodeIt;

		T value = nodeIt->value;
		m_nodes.pop_front();
		return value;
	};

	bool IsEmpty() {
		return m_keys.empty();
	};

	void Clear() {
		m_keys.clear();
		m_nodes.clear();
	}; 

};
