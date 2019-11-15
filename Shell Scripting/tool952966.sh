#1o erwtima
if [ $# -eq 0 ]; then
	echo "4952-5966"
	exit 1
fi

if [ $# -eq 2 ]; then
	sed 's/^\#//g' <  event.dat 		#afairoume apo tin arxi(^) ka8e grammis to simvolo #
	exit 1
fi



#2o erwtima
if [ $# -eq 4 ]; then 				        #elegxoume an to sinolo orismatwn einai iso me to 4

	awk -F'|' -v  pat=^$4 '$1~pat {print $2,$3,$5}' event.dat  #sti metavliti pat dinoume to orisma 4(id) kai tipwnoume
								   #gia to id afto tis stiles 2,3,5

fi

#3o erwtima
if [ $1 = "--firstnames" ]; then 			#elegxoume an to orisma 1 einai to --firstnames
	awk -F'|' '{print $3}' <  event.dat | sort      #orizoume field seperator to | kai tipwnoume ti stili firstnames(3)
fi

if [ $1 = "--lastnames" ]; then				#elegxoume an to orisma einai to --lastnames
	awk -F'|' '{print $2}' <  event.dat | sort	#antistoixa tipwnoume ti stili me ta lastnames(2)
fi

#4o erwtima
if [ $1 = "--born-since" ]; then			#elegxoume an to orisma pou do8ike einai to --born-since
	awk -F'|' -v pat1=$2 -v pat2=$4 '$5>=pat1 && $5<=pat2 {print $5, $0}' event.dat | sort | sed 's/[^ ]* *//'   #stis metavlites pat1 kai pat2 ekxwroume tis imerominies
														     #anamesa stis opoies anazitoume kai me to logiko AND
														     #vriskoume poies grammes tairiazoun, tipwnontas aftes.
fi

#5o erwtima - a
if [ $1 = "--socialmedia" ]; then
	awk -F'|' '{print $9}' event.dat | sed '/socialmedia/d' | sort > media.out				#tipwnoume tin stili 9(social media) se ena arxeio me onoma
														#media apo to opoio afairoume tin prwti grammi kai to sortaroume
														
awk '{social[$1]++} END {for (media in social) print social[media], media}' media.out > media2.out 		#gia ka8e monadiki leksi pou vriskoume sto media afksanoume to
														#metriti tis kata 1, grafontas to ka8e socialmedia kai ton
														#ari8mo emfanisewn tou se ena ksexwristo arxeio media2

awk  '{print $2 "\t\t" $1}' media2.out | sort -t' ' -k2						#taksinomoume alfavitika kai allazoume ti seira twn stilwn
												#wste na emfanizonte prwta ta socialmedia kai meta o metritis
fi

#5o erwtima - b
if [ $3 = "--edit" ]; then			#an to orisma 3 einai to --edit tote

	awk -F'|' -v col=$5 -v id=$4 -v val=$6 '{if ($1==id && col>=2 && col<=8) {$col = val;} print $1, $2, $3}' event.dat | sort    #an to id vre8ei antistoixei se kapio atomo
																      #kai to orisma tis stilis einai 2<=col<=8
																      #vazoume sto ari8mo tis stilis pou do8ike stin
																      #eisodo, tin timi pou perastike apo to orisma 6 sti val

fi







