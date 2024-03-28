
# Choco.cpp

> Once you want a sweet CHOCOLATE🍫

Photo of milk chocolate

<img src="./banner.png" width="192" height="192" />

## Code guide

In Choco.cpp, we use Data-oriented-design.

So struct is more often being used instead classes.

```cpp
struct A {
    // Public members are CapitalizedCamelCase
    int PublicMember;
    
    // Private members are lowerCasedCamelCase
    int privateMember;
    
    // Public methods are CapitalizedCamelCase
    void PublicCall();
    
    // Private members are lowerCasedCamelCase
    void internalCall();
};
```

> Long story in short, public things are Capitalized and private things are lowerCased.

Also, you can mark them private if you want.

```cpp
struct A {
    int PublicMember;
    
private:
    int privateMember;
};
```

## License

BSD 2-Clause License
