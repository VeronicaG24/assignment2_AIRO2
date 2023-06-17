(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents 
)

(:types robot region waypoint assignment
)

(:predicates
		(robot_in ?v - robot ?r - region) 
		(visited ?r - region ) 
		(connected ?r1 ?r2 - region)
		(assignment_in ?ass -assignment ?r - region)
		
)	    

(:functions 
		(act-cost) 
		(triggered ?from ?to - region) 
		(dummy)
		(distance ?from ?to - region)
		(number_ass)
)

(:durative-action localize
		:parameters (?v - robot ?from ?to - region)
		:duration (= ?duration distance)
		:condition (and (at start (robot_in ?v ?from)))
	    :effect (and (at start (not (robot_in ?v ?from))) 
			         (at start (increase (triggered ?from ?to) 1))
		             (at end (robot_in ?v ?to)) 
					 (at end (assign (triggered ?from ?to) 0)) 
					 (at end (visited ?to)) 	
                     (at end (increase (act-cost) (dummy))))
)

(:action  collect
	:parameters (?v -robot ?ass -assignment ?r -region)
	:precondition (and(assignment_in ?ass ?r) (robot_in ?v ?r))
	:effect (and (not(assignment_in ?ass ?r)) (decrease (number_ass) 1))
)


)
