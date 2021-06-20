# ESD_assignment.
# This is embbeded software design assignment.
# The assignment is to design a circular buffer.
# The buffer size is 8.
# 
#
# Buffer_testing1.c is the first version of our code but it doesn't work.
# Buffer_testing2.c is the second version of our code that based on the coding given by our lecturer.
# Buffer_main.c is the main coding write by our group. In main.c consist 2 buffer which called buffer_1 with size of 8 and buffer_2 with size of 8.
# buffer_1 is to stored the items that produce by thread chef_1 and chef_2.
# buffer_2 is to stored a recored data that how many items had sent out by thread waiter_1 and waiter_2.
# When chef_1 and chef_2 produce something it will stored to buffer_1 and waiter_1 and waiter_2 will sent out the thing, when the items had sent out, the space in buffer_1 will increase.
# thread waiter_1 and waiter_2 will update buffer_2 to let cashier know how many item sent out and the cashier will print out the bils. 
