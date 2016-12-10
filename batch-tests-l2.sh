for cache_size_L1 in {2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152}
do
	for block_size_L1 in {64,128,256,1024,2048}
	do
	for associativity_L1 in {0,1,2,4,8}
		do
			bsas_L1=$((${block_size_L1}*${associativity_L1}))
			if [ ${cache_size_L1} -lt $bsas_L1 ]
				then
					echo L1:${cache_size_L1} ${block_size_L1} ${associativity_L1} 'wrong params - less' >> wrong.txt
			else
			# get latency
			  l1_latency=`./cacti/cacti ${cache_size_L1} ${block_size_L1} ${associativity_L1}`
			  if [ ''${l1_latency} == '' ]
			  	then
			  		echo L1:${cache_size_L1},${block_size_L1},${associativity_L1},'wrong params' >> wrong.txt
			  else
			  	if [ ${l1_latency} -le 0 ]
			  		then
			  			echo L1:${cache_size_L1},${block_size_L1},${associativity_L1},'wrong params' >> wrong.txt
			  	else
			  		if [ ${associativity_L1} -eq 0 ]
			  			then
			  				associativity_L1=$((${cache_size_L1}/${block_size_L1}))
			  		fi

			  		for cache_size_L2 in {16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216}
						do
							expected_size_L2=$((${cache_size_L1}*2))
							if [ ${cache_size_L2} -lt ${expected_size_L2} ]
								then
									continue
							fi
							for block_size_L2 in {64,128,256,1024,2048}
							do
							for associativity_L2 in {0,1,2,4,8}
								do
									bsas_L2=$(( ${block_size_L2} * ${associativity_L2} ))
									if [ ${cache_size_L2} -lt $bsas_L2 ]
										then
											echo L2:${cache_size_L2} ${block_size_L2} ${associativity_L2} 'wrong params - less' >> wrong.txt
									else
										l2_latency=`./cacti/cacti ${cache_size_L2} ${block_size_L2} ${associativity_L2}`
									  if [ ''${l2_latency} == '' ]
									  	then
									  		echo L2:${cache_size_L2},${block_size_L2},${associativity_L2},'wrong params' >> wrong.txt
									  else
									  	if [ ${l2_latency} -le 0 ]
									  		then
									  			echo L2:${cache_size_L2},${block_size_L2},${associativity_L2},'wrong params' >> wrong.txt
									  	else
									  		if [ ${associativity_L2} -eq 0 ]
									  			then
									  				associativity_L2=$((${cache_size_L2}/${block_size_L2}))
									  		fi
											  data=`./sim ./trace/1.trace 1 0 0 100 \
												  ${cache_size_L1} ${block_size_L1} ${associativity_L1} 0 ${l1_latency} \
											  	${cache_size_L2} ${block_size_L2} ${associativity_L2} 3 ${l2_latency} \
											  	0 0 0 0 0`
										  	echo ${cache_size_L1},${block_size_L1},${associativity_L1},0,${l1_latency},${cache_size_L2},${block_size_L2},${associativity_L2},3,${l2_latency},${data} >> right-trace1-L2.txt
											fi
										fi
									fi
								done
							done
						done
					fi
				fi
			fi
  	done
  done
done
