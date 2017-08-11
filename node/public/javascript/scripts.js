function displayLists(jsonString) {
    // console.log(jsonFile['person']['-id']);
    let json = JSON.parse(jsonString);
    let content = $('#content');
    let toInsert = "";
    let fName = '';
    let lname = '';
    let city;
    let date;
    content.html('<br />');
    $.each(json.person, (index, element) => {
        toInsert = '';
        fName    = '';
        lName    = '';
        city     = '';
        date     = '';

        toInsert += '<div class="person col-xs-12 col-sm-6">';
        $.each(element, (index, value) => {
            if(index === '-id') {
                toInsert += `<span class='id'>#${value}</span>`;
            }
            if(index === 'firstName') {
                fName = value;
            }
            if(index === 'lastName') {
                lName = value;
            }
            if (index === 'city') {
                city = value;
            }
            if (index === 'dateUpdated') {
                date = value;
            }
        });
        toInsert += ' ' + fName + ' ' + lName;
        toInsert += '<div class="hidden-sm hidden-xs">';
        toInsert += `<br /> ${city}`;
        toInsert += `<br /> ${date}`;
        toInsert += '<br />';
        toInsert += '</div>';
        content.append(toInsert);
    });

}

function displaySpecific(jsonString) {
    let json     = JSON.parse(jsonString);
    let content  = $('#specific');
    let toInsert = '';
    let id;
    let fName;
    let lName;
    let age;
    let city;
    let deta;
    let date;

    content.html('');

    $.each(json.person, (index, element) => {
        $.each(element, (index, value) => {
            switch (index) {
              case '-id':
                id = value;
                break;
              case 'lastName':
                lName = value;
                break;
              case 'firstName':
                fName = value;
                break;
              case 'age':
                age = value; 
                break;
              case 'city':
                city = value;
                break;
              case 'details':
                deta = value;
                break;
              case 'dateUpdated':
                date = value;
                break;
              default:
                console.log(`Key:Value ${index}:${value} not handled.`);
            }
        });
        toInsert += '<div>';
        toInsert += 'Name: <span class="out">'         + fName + ' ' + lName + '</span><br />';
        toInsert += 'Age: <span class="out">'          + age   + '</span><br />';
        toInsert += 'City: <span class="out">'         + city  + '</span><br />';
        toInsert += '<span class="hidden-xs hidden-sm">Details: <span class="out">' + deta  + '</span></span><br />';
        toInsert += 'Date Updated: <span class="out">' + date  + '</span><br />';
        toInsert += '</div>';
        content.append(toInsert);
    });
}

$(document).on('click', '.dropdown', (e) => {
    let listName = e.target.value;

    $.get('/', { which: listName },  (data) => {
        setInterval(displayLists(data), 30000);
    });
});

$(document).on('click', '.person .id',  (e) => {
    let personId = $(e.target).text().substring(1);

    $.get('/', { "id": personId }, (data) => {
        displaySpecific(data);
    });
});
 
$(function () {
    // loadListNames();
    'use strict';
});
