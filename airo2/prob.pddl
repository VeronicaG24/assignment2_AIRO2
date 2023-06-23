(define (problem prob1)
(:domain localization)
(:objects
     a1 a2 a3 a4 - assignment
     r0 r1 r2 r3 r4 r5 - region
     R2D2 - robot
)
(:init
    (robot_in R2D2 r0)

    (= (act-cost) 0)
    (= (dummy) 0)

    (is_in a1 r1) (is_in a2 r2) (is_in a3 r3) (is_in a4 r4)
 )

(:goal 
     (and (visited r1) (visited r2) (visited r3) (visited r4))
)
     (:metric minimize (act-cost))
)
