(define (problem prob1)
(:domain localization)
(:objects
     r0 r1 r2 r3 r4 - region
     R2D2 - robot
     a1 a2 a3 a4 -assignment
)
(:init
     (robot_in R2D2 r0)
     (assignment_in a1 r1)
     (assignment_in a2 r2)
     (assignment_in a3 r3)
     (assignment_in a4 r4)
     (= (act-cost) 0)
     (= (dummy) 0)
     (= (number_ass) 4)
)
(:goal 
     (and (=(number_ass) 2))
)
(:metric minimize (act-cost) )
)
