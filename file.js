function test(var1, var2) {

    this.name = "simo";
    this.age = 22;


    this.decribe = function() { return this.name + " yoo"}
}


test.decribe();