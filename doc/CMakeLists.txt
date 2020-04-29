add_custom_target(doc)

add_latex_document(assignment-template.tex
    TARGET_NAME assignment-template
    EXCLUDE_FROM_ALL
)

add_latex_document(assignment-1a_b.tex
    TARGET_NAME assignment-1a_b
    EXCLUDE_FROM_ALL
)

add_latex_document(scribe-2020-02-27.tex
    TARGET_NAME scribe-2020-02-27
    EXCLUDE_FROM_ALL
)

add_latex_document(scribe-carla-2020-02-27.tex
    TARGET_NAME scribe-carla-2020-02-27
    EXCLUDE_FROM_ALL
)

add_latex_document(assignment-policy-keywords.tex
    TARGET_NAME assignment-policy-keywords
    EXCLUDE_FROM_ALL
)

add_latex_document(pagerank-paper-review.tex
    TARGET_NAME pagerank-paper-review
    EXCLUDE_FROM_ALL
)

add_dependencies(doc assignment-template assignment-1a_b scribe-2020-02-27 scribe-carla-2020-02-27 assignment-policy-keywords pagerank-paper-review)
