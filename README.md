# Algorithms-and-Theoretical-CS-class-project-22-23

## Overview

Developed, analyzed, and implemented an algorithm that utilizes trees and other data structures to manage an algorithmical problem. Achieved the maximum grade possible (30 cum laude/30) by meeting the most challenging time and space complexity constraints among those proposed.

## Project Specification

Consider a highway described as a sequence of service stations. Each service station is located at a distance from the beginning of the highway, expressed in kilometers as a non-negative integer. There are no two service stations with the same distance: each service station is uniquely identified by its distance from the beginning of the highway.

Each service station is equipped with a fleet of electric rental vehicles. Each vehicle has a range, expressed in kilometers as a positive integer. The vehicle fleet of a single station comprises at most 512 vehicles. Renting a car from station s, it is possible to reach all stations whose distance from s is less than or equal to the car's range.

A journey is identified by a sequence of service stations where the driver makes stops. It begins at a service station and ends at another, passing through zero or more intermediate stations. Assume that the driver cannot backtrack during the journey and rents a new car whenever making a stop at a service station. Therefore, given two consecutive stops s and t, t must always be farther from the starting point than s, and t must be reachable using one of the available vehicles at s.

The project's objective is as follows: given a pair of stations, plan the route with the fewest number of stops between them. In case multiple routes have the same minimum number of stops (i.e., tied), choose the route that prefers stops with shorter distances from the beginning of the highway. In other words, consider the set of n tied paths P = {p1, p2, . . . pn}, where each path is a tuple of m elements pi = ⟨pi,1, pi,2, . . . pi,m⟩ representing the distance from the beginning of the highway of each stop in order. Choose the unique path pi such that there is no other pj with the same k final stops preceded by a stop with a smaller distance.
