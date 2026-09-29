# Name: Awni AlQuraini
# Date: 9/23/2026
# Title: Lab 1 - Area and Perimeter shell script
#!/bin/sh
echo Executing $0
# Computes area using bc b/c native expr does not support floating point arithmetic
area(){
	radius=$1
	echo "The area of the circle is: "
	echo "$radius * $radius * 3.14" | bc
}
# computers perimeter using bc for the same reason above
perimeter(){
	radius=$1
	echo "The perimeter of the circle is: "
	echo "2 * $radius * 3.14" | bc
}
# here is the control loop that drives the script
response="Yes"
while [ $response != "No" ]
do
	echo "Enter the circle radius: "
	read radius
	if [ "$radius" -lt 0 ]
	then
		echo "Radius value not valid!"
		continue
	fi
	area "$radius"
	perimeter "$radius"
	echo "Do you want to try this again? [Yes/No]?"
	read response
done
