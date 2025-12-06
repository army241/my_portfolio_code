while(True):
    num1 = float(input())
    operation= input()
    num2 = float(input())
    if operation=='+':
        print(" = ")
        print(num1+num2)
    elif operation=='-':
        print(" = ")
        print(num1-num2)
    elif operation=='*':
        print(" = ")
        print(num1*num2)
    elif operation=='/':
        if num2 != 0:
            print(" = ")
            print(num1 / num2)
        else:
            print("Cannot divide by zero!")
    else:
        print("incorrect operation")

