pre_allocate_error_list <- function(array_len, metrics) {
  error_list <- list()
  for (metric in metrics) {
    error_list[[metric]] <- rep(0, array_len)
  }
  return(error_list)
}

calc_rel_error <- function(v, v_approx, metric) {
  if (metric == "norm") {
    rel_error <- sqrt(sum((v - v_approx)^2) / sum(v^2))
  } 
  else if (metric == "l1norm") {
    rel_error <- sum(abs(v - v_approx))/sum(abs(v))
  } else {
    coordwise_err <- abs((v - v_approx) / v)
    rel_error <- switch(metric,
      percentile5 = { quantile(coordwise_err, 0.05) },
      median = { median(coordwise_err) },
      percentile95 = { quantile(coordwise_err, 0.95) }
    )
  }
  return(rel_error)
}