(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents
)

(:types robot region
)

(:predicates
		(robot_in ?v - robot ?r - region) 
		(visited ?r - region)
		(collected ?r - region)
)

(:functions 
		(act-cost) 
		(triggered ?from ?to - region) 
		(dummy)
		(get ?r - region)
)

(:durative-action goto
		:parameters (?v - robot ?from ?to - region )
		:duration (= ?duration 100)
		:condition (and (at start (robot_in ?v ?from)))
	    :effect (and (at start (not (robot_in ?v ?from))) 
			         (at start (increase (triggered ?from ?to) 1))
		             (at end (robot_in ?v ?to)) 
					 (at end (assign (triggered ?from ?to) 0)) 
					 (at end (visited ?to)) 
                     (at end (increase (act-cost) (dummy))))
)
(:durative-action collect
	:parameters (?v - robot ?r - region)
	:duration (= ?duration 5)
	:condition (and 
		(at start (robot_in ?v ?r))
		(at start (> (get ?r) 0))
		)
	:effect ( and
		(at end (collected ?r))
		)
	)
	
)

