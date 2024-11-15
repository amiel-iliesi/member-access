# Part 0: Reading A New Set Of Files

## Preamble: Helpful Tool For Learning Comfortably
When working with multiple files, it is a *really* good idea to be able to have
multiple files open at a time and visible so you can compare different parts without
having to keep switching tabs, or opening new files. It really speeds the learning
process up.

If you're using **Vim**, you should consider learning about "windows". They have
done wonders for me when it comes to learning new files. I never leave home without
it :)
* https://vimdoc.sourceforge.net/htmldoc/windows.html

Here is an example:

![vim Window splitting](./figures/windows%20in%20Vim.png)

## How to Even Begin
For this first set of files, we have a bit of a mess to deal with. If we open our
files and start digging around and try and understand it all at once, we will quickly
get overwhelmed at the sheer number of things being introduced to us. Even if we are 
able to understand this first set of files, things will only escalate from here.

Clearly, this is not a winning strategy. We need a way to start small, and understand
a new file-set piece by piece.

Let us work forward in the smallest increments possible, this way we get familiar with
the code much more quickly.

## 1a: Let's See What It Does
*If the code is functional*, running it and observing the output is the best way to
get familiar with it. The current example given *is* functional, so we can try that
here. Try running the code and coming back.

...

Welcome back! I will paste the output here for convenience and we will refer to it
going forward:
> `1/2 + -3/4 = -1/4`

It looks like the purpose of these files is to work with fractions! And it looks
like they can be added and outputted already. Just with this short observation we
learned a lot of what the program is about, and what it is capable of. We can now look
at [main.cpp](./reference%20files/main.cpp) and start putting the pieces together.

## 1b: [main.cpp](./reference%20files/main.cpp)
[main.cpp](./reference%20files/main.cpp) seems to have very little in it so far, but we can still make a few
observations before we proceed, like how the user is expected to interact with these
fractions, syntax and the like.

## 2: [fraction.h](./reference%20files/fraction.h)
Next stop: [fraction.h](./reference%20files/fraction.h). Header files (in general) are like our table of contents,
and is the case for the `Fraction` class. Before we look at any implementations *ever*,
it's a great idea to get a birds-eye view of what a class is capable of before we look
at implementations for specific functions or details.

Please open up the [fraction.h](./reference%20files/fraction.h) file and study it closely before coming back, and
please hold off going to look at implementations for now. The benefits of this
slow-forward approach will soon become clear.

...

OK, welcome back! What can we know about this class, by looking at the header, and
header *only*?

We know what data each fraction is keeping track of:
- an integer numerator
- an integer denominator

We know what functions it currently supports:
- Three different constructors (no parameters, two integers, or another fraction),
- addition between fractions,
- output from ostream,
- ...and a few private functions that are potentially not super clear yet.
  - This is a good sign that we could potentially comment these functions a bit more.

After considering all of these things, we have a pretty good overview about what this
class is currently capable of, as well as how we are expected to interact with it.
With this, we can confidently proceed to the implementation in [fraction.cpp](./reference%20files/fraction.cpp) and
understand what we're looking *at*, and looking *for*.

## 3: [fraction.cpp](./reference%20files/fraction.cpp)
This is where all of the magic happens, and now that we've put in the work to
understand the structure, we can look at any details we're curious about without
feeling lost.

We can begin to understand the class a bit more deeply if we track some behavior we've
previously observed and try to follow it through the program.

For example, if we try to understand how the adding works in [main.cpp](./reference%20files/main.cpp), lets look
at the outermost function call. I will keep running track of the path we came from
as we go in this example, but this will be left as an exercise for subsequent
examples.

## 3a: Adding Fractions
First, we look in [main.cpp](./reference%20files/main.cpp) to identify where we want to start looking. We see the
following in [main.cpp](./reference%20files/main.cpp):
```cpp
f1 + f2
```

Which means the addition is being performed by the addition operator. Lets start
there, and follow it where it goes!
```cpp
Fraction Fraction::operator+(const Fraction& other)
{
	Fraction f_new(*this); // copy this obj into new fraction
	f_new.add(other);
	return f_new;
}
```

Lets see what the first line does. It looks like it calls the copy constructor from
above in the file to make a copy of our current object, and it stores it in a new
`Fraction` object called `f_new`.

Then it calls the `add` function with the `other` fraction on our new fraction. So
far this is making sense, but lets see exactly how it's doing this add; let's follow
the `add` function and observe.
```cpp
void Fraction::add(const Fraction& other)
{
	//a/b + c/d = (ad + cb)/(bd)
	numerator *= other.denominator;
	numerator += other.numerator * denominator;

	denominator *= other.denominator;

	reduce();
	normalize();
}
```

Just to keep track, so far we are here:
```
adding in main (`f1 + f2`)
└─ operator+
   ├─ copy construct new function (`Fraction f_new(*this)`)
   └─ [->] add two fractions (`f_new.add(other)`)
```

It seems a bit daunting at first! A bit more complicated than you might have
originally thought. Helpfully though, there seems to be a comment about the
math being done right below.

If you can convince yourself about the math being done being the correct way to add
two fractions together, then this function seems to make complete sense!

## 3b: The Other Half After Adding
Let's go now towards the bottom of this function where we have a few calls that
appear to be without context. We can recall from [fraction.h](./reference%20files/fraction.h) that `reduce()` and
`normalize()` were commented/categorized as aesthetic/prettify functions, which might
start to give us an idea of what they do.

Reduce seems to make enough sense on it's own; it is clear enough by name alone. So
for now we will skip it, but definitely follow the chain of calls yourself if you
are curious! There is some interesting work going on there.

—but `normalize()` seems a bit less clear, so let's see what that does.

...

We are currently here now:
```
adding in main (`f1 + f2`)
└─ operator+
   ├─ copy construct new function (`Fraction f_new(*this)`)
   └─ add two fractions (`f_new.add(other)`)
      ├─ do the math
      ├─ reduce the fraction (`reduce()`)
      └─ [->] (`normalize()`)?
```

Now, looking at `normalize()`, lets see what it does:
```cpp
void Fraction::normalize()
{
	if (numerator < 0 and denominator < 0) { //-a/-b -> a/b
		numerator = -numerator;
		denominator = -denominator;
	}
	else if (numerator >= 0 and denominator < 0) { // a/-b -> -a/b
		numerator = -numerator;
		denominator = -denominator;
	}
}
```

It looks like it it's taking different forms of fractions (like a negative over a
negative), and converting them into the more common forms. That makes sense,
considering the category that this function was in—in the header file!

Lets have an overview of how we got here, all the way through the function calls:
```
adding in main (`f1 + f2`)
└─ operator+
   ├─ copy construct new function (`Fraction f_new(*this)`)
   └─ add two fractions (`f_new.add(other)`)
      ├─ do the math
      ├─ reduce the fraction (`reduce()`)
      └─ give it a form that most people like (`normalize()`)
```

Following it this way, it seems to make a whole lot of sense! And we weren't
overwhelmed at the end of it. We just took small steps forward, and just by following a simple
step-by-step path through the files, we ended up understanding each individual piece, and now
the project as a whole!

## Next Steps
We will be looking at different files working together, as well as some basic member access.
Things are going to get a bit more complicated, but you should have the tools now to
successfully understand the upcoming project.
