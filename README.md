# General-DL-net-AI
This is the WIP application formed from a total rethinking of how AIs should operate. 

## General idea behind it in as few words as possible while being understandable:
A more efficient AI framework similar to neural-nets; However, it is based on several fundamental operations (rather than a sigmoid), self-compression for speed & Arkam's razor, and has a triad of networks working in conjunction.

<hr>
<h3> Low-Level: </h3>

1. Having a suite of fundamental mathematical equations that a "node can choose"\* instead of a sigmoid. <i>This is to decrease the amount of resources that it takes, as a series of sigmoids can reach the same result at the cost of more iterations and nodes. Also having a suite of fundamental mathematical functions should work better with compression as compression shouldn't try to achieve the smallest amount of sigmoids, but the smallest amount of base mathematical equations</i>
2. Intermittent network compression that trims consistently deactivated nodes & connections, compresses sets of nodes that can be defined in a more concise mathematical equation with minimal loss, and adds in more nodes in spots that seem to have situational, but not general prediction (this is because situational prediction shows that it is on the right track but needs to refine further)
3. Randomly turning nodes&connections back on, etc (the conventional stuff)
4. Mediate iteration & depth problem by averaging all values (or its mathematical equation's equivalent) and changing the backpropagation value down a path to take into account change in forward weights and the node's equation. 

<hr>
<h3> High-level:</h3>

1. One neural layer on top of initial for nodes, layers, biases, etc (this isn't new)
2. Another persistent neural layer on top of the rest for changing/influencing settings during runtime.
