(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents
)

(:types robot region assignment
)

(:predicates
		(robot_in ?v - robot ?r - region) 
		(visited ?r - region )
		(checked ?from ?to - region)
		(collected ?ass - assignment)
		(is_in ?ass - assignment ?r - region)
		(not_feasible ?from ?to - region)
		(try)
)

(:functions 
		(act-cost) 
		(triggered ?from ?to - region) 
		(dummy)
		(check_connection ?from ?to - region)
)

(:durative-action checking
	:parameters (?v - robot ?from ?to -region)
	:duration (= ?duration 100)
	:condition (and (at start (robot_in ?v ?from)))
	:effect (and (at start (increase (check_connection ?from ?to) 1))
				 (at end (checked ?from ?to))
				 (at end (checked ?to ?from))
				 (at end (assign (check_connection ?from ?to) 0)))
)

(:durative-action localize
		:parameters (?v - robot ?from ?to - region)
		:duration (= ?duration 100)
		:condition (and (at start (robot_in ?v ?from)) (at start (checked ?from ?to)) (at start (try)))
	    :effect (and (at start (not (robot_in ?v ?from))) 
			         (at start (increase (triggered ?from ?to) 1))
		             (at end (robot_in ?v ?to)) 
					 (at end (assign (triggered ?from ?to) 0)) 
					 (at end (visited ?to)) 
                     (at end (increase (act-cost) (dummy))))
)

)

)
