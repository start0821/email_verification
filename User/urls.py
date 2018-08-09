from django.conf.urls import url,include
from django.contrib import admin
from User import views

app_name = 'accounts'
urlpatterns = [
    url(r'', include('django.contrib.auth.urls')),
    url(r'^register/$', views.UserCreateView.as_view(), name='register'),
    url(r'^register/done/$', views.UserCreateDoneTemplateView.as_view(), name='register_done'),
    url(
        r'^activate/(?P<uidb64>[0-9A-Za-z_\-]+)/(?P<token>[0-9A-Za-z]{1,13}-[0-9A-Za-z]{1,20})/$',
        views.UserActivateView.as_view(),
        name='activate'
    ),
    url(r'^sign_in/$', views.sign_in, name='sign_in'),
    # url(r'^search/$', views.sign_in, name='sign_in'),
    # url(r'^information/$', views.sign_in, name='sign_in'),
    
    
]
