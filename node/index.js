const express = require('express');
const app = express();
const options = {
    root: __dirname + '/public/',
    dotfiles: 'deny',
    headers: {
        'x-timestamp':Date.now(),
        'xsent': true
    }
};

app.get('/managelist', (req, res) => {
    res.redirect('http://localhost:666');
});

app.get('/', (req, res) => {
    res.sendFile('index.html', options, (err) => {
        if (err) {
            res.send('404, file not found.')
        }
    })
});

app.listen('1337');
