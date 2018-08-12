from django import forms
from django.contrib.auth.forms import ReadOnlyPasswordHashField
from django.utils.translation import ugettext_lazy as _
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.tokens import PasswordResetTokenGenerator
from django.contrib.sites.shortcuts import get_current_site
from django.template.loader import render_to_string
from django.utils.http import urlsafe_base64_encode
from django.core.mail import EmailMessage
from django.utils.encoding import force_bytes

class UserCreateForm(UserCreationForm):
    username = forms.CharField(required=True,
                               label='',
                               widget=forms.TextInput(attrs={'placeholder':"아이디",'class':"form-control"}),
                               )
    email = forms.EmailField(required=True,
                             label='',
                             widget=forms.TextInput(attrs={'placeholder':"대학교 이메일을 입력해주세요",'class':"form-control",'type':"email"}),
                             )
    first_name = forms.CharField(required=True,
                                 label='',
                                 widget=forms.TextInput(attrs={'placeholder':"First Name : 성",'class':"form-control"}),
                                 )
    last_name = forms.CharField(required=True,
                                label='',
                                widget=forms.TextInput(attrs={'placeholder':"Last Name : 이름",'class':"form-control"}),
                                )
    password1 = forms.CharField(label='',required=True,widget=forms.PasswordInput(attrs={'placeholder':"비밀번호",'class':"form-control",'type':"password"}))
    password2 = forms.CharField(label='',required=True,widget=forms.PasswordInput(attrs={'placeholder':"비밀번호 확인",'class':"form-control",'type':"password"}))
    class Meta:
        model = User
        fields = ('username','email', 'first_name' , 'last_name', )


class UserChangeForm(forms.ModelForm):
    # 비밀번호 변경 폼
    password = ReadOnlyPasswordHashField(
        label=_('Password')
    )

    class Meta:
        model = User
        fields = ('email', 'password', 'last_name', 'first_name', 'is_active', 'is_superuser')

    def clean_password(self):
        # Regardless of what the user provides, return the initial value.
        # This is done here, rather than on the field, because the
        # field does not have access to the initial value
        return self.initial["password"]


class WebUserCreationForm(UserCreateForm):
    terms = forms.BooleanField(
        label=_('Terms of service'),
        widget=forms.CheckboxInput(
            attrs={
                'required': 'True',
            }
        ),
        error_messages={
            'required': _('You must agree to the Terms of service to sign up'),
        }
    )
    privacy = forms.BooleanField(
        label=_('Privacy policy'),
        widget=forms.CheckboxInput(
            attrs={
                'required': 'True',
            }
        ),
        error_messages={
            'required': _('You must agree to the Privacy policy to sign up'),
        }
    )

    def __init__(self, *args, **kwargs):
        # important to "pop" added kwarg before call to parent's constructor
        # print(kwargs)
    # if 'request' in kwargs.keys():
        self.request = kwargs.pop('request', None)
        super(UserCreateForm, self).__init__(*args, **kwargs)

    def save(self, commit=True):
        user = super(WebUserCreationForm, self).save(commit=False)

        if commit:
            user.is_active = False
            user.save()

            # Send user activation mail
            current_site = get_current_site(self.request)
            subject = (_('Welcome To %s! Confirm Your Email') % current_site.name)
            message = render_to_string('registration/user_activate_email.html', {
                'user': user,
                'domain': current_site.domain,
                'uid': urlsafe_base64_encode(force_bytes(user.pk)),
                'token': PasswordResetTokenGenerator().make_token(user),
            })
            email = EmailMessage(subject, message, to=[user.email])
            email.send()

        return user
