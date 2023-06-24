(define (problem prob1)
(:domain localization)
(:objects
     r0 r1 r2 r3 r4 r5 - region
     R2D2 - robot
)
(:init
    (robot_in R2D2 r0)

    (= (act-cost) 0)
    (= (dummy) 0)

     (= (get r1) 1) (= (get r2) 1) (= (get r3) 1) (= (get r4) 1)
 )

(:goal 
     ; if you want change the region of the assignments, you have to change r1 and/or r4 
     ; in collected predicate; obviously the cost may change
     (and (collected r1) (collected r4) (robot_in R2D2 r5))
)
     (:metric minimize (act-cost))
)


