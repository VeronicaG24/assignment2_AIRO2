(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents
)

(:types robot region assignment
)

(:predicates
		(robot_in ?v - robot ?r - region) 
		(visited ?r - region)
		(collected ?ass - assignment)
		(is_in ?ass - assignment ?r - region)
)

(:functions 
		(act-cost) 
		(triggered ?from ?to - region) 
		(dummy)
)

(:durative-action localize_and_take
		:parameters (?v - robot ?from ?to - region ?a - assignment)
		:duration (= ?duration 100)
		:condition (and (at start (robot_in ?v ?from)))
	    :effect (and (at start (not (robot_in ?v ?from))) 
			         (at start (increase (triggered ?from ?to) 1))
		             (at end (robot_in ?v ?to)) 
					 (at end (assign (triggered ?from ?to) 0)) 
					 (at end (collected ?a))
					 (at end (visited ?to)) 
                     (at end (increase (act-cost) (dummy))))
)

)
