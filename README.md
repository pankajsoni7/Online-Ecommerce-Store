# Online-Ecommerce-Store

## Overview

The core concept of this project is to facilitate the purchase of products based on the available information. It aims to create an online platform specifically for selling cameras, designed to simplify inventory management, streamline order processing, and organize customer information effectively.

This system will leverage various data structures and algorithms to ensure efficient handling of the store's inventory and smooth processing of orders. Additionally, the project will feature a user-friendly interface to enhance the shopping experience for customers.

Beyond the basic functionalities, this project will employ a variety of data structures to improve the system's performance and overall efficiency.

In summary, this project will illustrate how data structures and algorithms can be practically applied in building an online store management system for camera sales, offering optimized solutions for data storage, retrieval, and order processing.

## Implemented Data Structures

• Linked List:

A linked list is a data structure that enables efficient insertion and deletion of elements.

Usage in Project:

This project employs linked lists to manage customer information and orders. The customer data, such as for delivery and takeaway options, is stored in a linked list. Linked lists were chosen over arrays due to their dynamic sizing capability, allowing the system to handle varying amounts of data flexibly.

• AVL (Adelson-Velsky and Landis) Tree:

An AVL tree is a self-balancing binary search tree that supports fast insertion, deletion, and search operations, making it ideal for handling large datasets.

Usage in Project:

The AVL tree is utilized to efficiently manage and maintain the store’s inventory. Operations like searching, inserting, and deleting items are performed with optimized performance. For example, the AVL tree handles all takeaway orders, with order IDs assigned by the user as keys for efficient insertion and deletion processes.


• Graphs:

Graphs are used in the project to represent areas where deliveries can be made. These graphs are structured using an adjacency matrix.

• Dijkstra’s Algorithm:

Dijkstra’s algorithm, a shortest-path algorithm, is implemented to facilitate efficient searching and navigation within the system. This algorithm finds the shortest path between two nodes—represented as cities—enabling the calculation of distances between them.

Usage in Project:

Dijkstra's algorithm is particularly useful in routing and serves as a subroutine for other graph algorithms. In this system, cities are represented as nodes, and the algorithm determines the shortest path between them, providing the distances between locations.

• Prim’s Algorithm:

Prim’s algorithm is used to compute the minimum spanning tree of a graph, helping to calculate the distances between different areas within a city.

Usage in Project:

Prim’s algorithm is applied to determine distances between city areas, with the goal of offering discounts based on minimum-distance routes rather than using prior distances. The key concept of Prim’s algorithm is that it incrementally builds a tree by selecting the minimum-weight edge connecting a new vertex to the existing tree. This approach ensures the minimum total weight of any possible spanning tree formed from the graph.
