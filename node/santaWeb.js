#!/usr/bin/env node

// Force Strict on EVERYTHING
'use strict';

// Set PORT and WEBROOT to constants, as well as all required modules
// Ensure no accidental tampering with my own server
const PORT      = 7546;
const WEBROOT   = './public/';
const HTTP      = require('http');
const FS        = require('fs');
const URL       = require('url');
const PATH      = require('path');
const QS        = require('querystring');
const CHALK     = require('chalk');
const REQUEST   = require('request');

//Create listen server on port PORT
HTTP.createServer(function(req, res) {
    // Get file directory structure, file extention, and
    // the content type.
    let fileLocation = URL.parse(req.url).pathname;
    let fileExtention = PATH.extname(fileLocation).slice(1);
    let contentType = getContentType(fileExtention);

    // Log important information for each request made to the server.
    console.log(CHALK.yellow('Request made:\n'));
    console.log(CHALK.yellow(`   File Location: ${fileLocation}`));
    console.log(CHALK.yellow(`   File Extentions: ${fileExtention}`));
    console.log(CHALK.yellow(`   Content Type: ${contentType}`));

    // Deal with request for favicon.ico by ending the request
    if (req.url === 'favicon.ico') {
        res.writeHead(200, {
            "Content-Type": "image/ico"
        });
        console.log(CHALK.green('   Favicon request handled'));
        res.end();
    }

    if (req.url === '/') {
        // Sends the user to the default landing page when they hit
        // port 9000 with no additional information..
        getFile(PATH.join(__dirname, WEBROOT, 'index.html'), res);
        res.writeHead(200, {
            "Content-Type": "text/html"
        });
    } else {
        // If the user has specified a page to navigate too...
        if (contentType === "unknown") {
            // If the requested file is not handled by the server,
            // serve the user a 415 error page.
            console.log(CHALK.red('   ERROR: 415 Unsupported Media Type\n    Ending user connection.'));
            res.writeHead(415, {
                'Content-Type': 'text/html'
            });
            getFile(PATH.join(__dirname, WEBROOT, '415.html'), res);
        } else {
            // If the requested file is a handleable type, attempt
            // to open and return the file.
            // If the user has requested a file in bin/
            getFile(PATH.join(__dirname, WEBROOT, fileLocation), res);
            res.writeHead(200, {
                "Content-Type": contentType
            });
        }
    }
}).listen(PORT);

// getFile grabs the file requested by the user, and serves it to the user
// Handles 404 errors if the requested file does not exist
// Handles 500 errors if the file exists, but is not accessable.
//      This is simulated with Test7CSS.html, which has been hit
//      with a 'chmod -r'.
function getFile(localPath, res) {
    console.log(CHALK.yellow(`   Attempting to retrieve file at: ${localPath}`));
    // Attempt to access the file before reading it.
    FS.open(localPath, 'r', (err, fd) => {
        if (!err) {
            FS.close(fd);
            FS.readFile(localPath, (err, data) => {
                if (!err) {
                    // If file can be read, server the file to the user
                    console.log(CHALK.green("   File has been retrieved\n"));
                    res.end(data);
                } else {
                    // If file can be accessed, but not read, serve
                    // to the user a 500 error page, as error must
                    // be on the servers end, not theirs.
                    console.log(
                        CHALK.red(
                            `   ${err.code} Cannot retrieve file at: 
                                    ${localPath}\n`));
                    res.writeHead(500, {
                        "Content-Type": "text/html"
                    });
                    getFile(PATH.join(__dirname, WEBROOT, '500.html'), res);
                }
            });
        } else {
            console.log(CHALK.red(`   ${err.code} Cannot retrieve file at: ${localPath}\n`));
            res.writeHead(404, {
                'Content-Type': 'text/html'
            });
            getFile(PATH.join(__dirname, WEBROOT, '404.html'), res);
        }
    });
}
//getContentType function takes in the file extention, and returns
//the content type corrisponding to that extention. Returns unknown\
//if file extention is not handled by this server.
function getContentType(ext) {
    let extentions = {
        "html"  : "text/html",
        "htm"   : "text/html",
        "css"   : "text/css",
        "js"    : "text/js",
        "png"   : "image/png",
        "jpg"   : "image/jpeg",
        "jpeg"  : "image/jpeg",
        "gif"   : "image/gif",
        "pdf"   : "application/pdf",
        "xml"   : "text/xml",
        "ico"   : "image/x-icon",
        "svg"   : "image/svg+xml"
    };

    for (let key in extentions) {
        if (key === ext) {
            return extentions[key];
        }
    }
    return "unknown";
}
