#!/usr/bin/nodejs


// -------------- load packages -------------- //
var express = require('express')
var path = require('path');
var hbs = require('hbs');
var fs = require('fs');
var request = require('request');

var app = express();

hbs.registerHelper('json', function (content) {
    return JSON.stringify(content);
});


// -------------- express initialization -------------- //
app.set('port', process.env.PORT || 8080 );

// tell express that the view engine is hbs
app.set('view engine', 'hbs');


// -------------- express endpoint definition -------------- //

app.use('/css', express.static(path.join(__dirname, 'css')));
app.use('/js', express.static(path.join(__dirname, 'js')));

function readFile (file) {
    return fs.readFileSync(file).toString().split("\n");
}

app.get('/load_file_worker', function(req, res){
    // console.log("load_file_worker anon()");
    // console.log(req.query.fileName);
    var text = readFile(req.query.fileName).reduce((a, b) => a + b);

    res.send(text);
});

app.get('/display', function(req, res){
    console.log("display anon()");

    var outputFolder = "./../code/output/" + req.query.simulationName + req.query.simulationIndex + "/";
    var globalFile = outputFolder + req.query.simulationName + "_global.txt";
    var eventFile = outputFolder + req.query.simulationName + "_event.txt";

    var obj = {
        "simulationName": req.query.simulationName,
        "simulationIndex": req.query.simulationIndex,
        "outputFolder": outputFolder,
        "globalFile": globalFile,
        "eventFile": eventFile,
    };

    res.render("display", obj);
});

app.get('/', function(req, res){
    console.log("home page anon()");
    var obj = {};
	res.render("homepage", obj);
});

// WILDCARD HANDLERS MUST COME AFTER ALL OTHER EXPLICIT ENDPOINTS
app.get('/:stuff', function(req, res){
    res.send("Oops, '/"+req.params.stuff+"' is not defined!");
});

// -------------- listener -------------- //
// The listener is what keeps node 'alive.'

var listener = app.listen(app.get('port'), function() {
  console.log('Express server started on port: '+listener.address().port);
});
