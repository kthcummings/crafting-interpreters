package com.craftinginterpreters.lox;

import java.util.ArrayDeque;
import java.util.Deque;

public class RpnPrinter implements Expr.Visitor<String>{
    String print(Expr expr){
        return expr.accept(this);
    }

    @Override 
    public String visitBinaryExpr(Expr.Binary expr) {
        // add operator to the stack
        Deque<String> stack = new ArrayDeque<>();
        stack.push(expr.operator.lexeme);
        stack.push(expr.right.accept(this));
        stack.push(expr.left.accept(this));
        return printStack(stack);
    }

    @Override 
    public String visitGroupingExpr(Expr.Grouping expr) {
        // RPN doesn't do grouping so we just get down to
        // the expression itself
        return expr.expression.accept(this);
    }

    @Override 
    public String visitLiteralExpr(Expr.Literal expr) {
        if(expr.value == null) return "nil";
        return expr.value.toString();
    }

    @Override 
    public String visitUnaryExpr(Expr.Unary expr) {
        // in RPN unary operators must be unique...
        // right now we only really have negation so we could just
        // expect that and hardcode it
        // but since we don't have a full interpreter maybe best not to
        // since this is just a printer we're going to add a '~' for now
        // this will indicate that the operator is a special unary operator
        // in the event we ever try to parse the notation this way
        Deque<String> stack = new ArrayDeque<>();
        String unaryOperator = "~" + expr.operator.lexeme;
        stack.push(unaryOperator);
        stack.push(expr.right.accept(this));
        return printStack(stack);
    }

    @Override
    public String visitTernaryExpr(Expr.Ternary expr) {
        // not implementing this
        return " ";
    }

    private String printStack(Deque<String> stack) {
        String output = stack.toString();
        output = output.replaceAll(",", "");
        return output.substring(1, output.length()-1);
    }
}
